#include "ConnectObject.h"
#include "ConnectObjectParam.h"

#include "DirectX_FrameWork1/Source/99-Lib/01-MyLib/07-Component/03-Collider/01-Collider2D/BoxCollider2D.h"

#include "../../../../99-Lib/01-MyLib/07-Component/06-Animator/01-SpriteAnimator/SpriteAnimator.h"
#include "../../../../99-Lib/01-MyLib/07-Component/02-Renderer/01-SpriteRenderer/SpriteRenderer.h"

int ConnectObject::instanceCounter = 0;

ConnectObject::ConnectObject()
{
	//生成番号を設定
	instanceCounter++;
	myInstanceNumber = instanceCounter;

	searchCollCell = ConnectObjectParam::searchCollCell;

	bodyCollider = nullptr;
	searchCollVert = nullptr;
	searchCollHori = nullptr;
}

void ConnectObject::Init()
{
	//本体部分の設定
	{
		//p_transform->position = hft::HFFLOAT3{ 0.f,0.f, 0.f };
		p_transform->scale = hft::HFFLOAT3{ 80.f, 80.f,1 };

		//スプライトレンダラー、アニメーターの設定
		{
			std::shared_ptr<Texture> tex = GetComponent<SpriteRenderer>()->LoadTexture("Assets/01-Texture/99-Test/char01.png");

			if (!tex)
			{
				return;
			}
			else
			{
				std::cout << "テストエネミーのテクスチャロード成功" << std::endl;
			}

			SpriteAnimator* p_spriteAnimator = AddComponent<SpriteAnimator>(hft::HFFLOAT2(3, 3));
			hft::HFFLOAT2 div = p_spriteAnimator->GetDivision();

			{
				SpriteAnimation anim(div, { 0,0 }, 9);
				anim.SetID(0);

				anim.SetType(SPRITE_ANIM_TYPE::LOOP);
				anim.SetPriority(0);
				float flame = 60;

				for (int i = 0; i < 9; i++)
				{
					anim.GetCellRef(i).flame = flame;
				}

				p_spriteAnimator->AddAnimation(anim);
			}
		}

		bodyCollider = AddComponent<BoxCollider2D>();
	}


	//縦横の審査用コライダーの設定
	{
		//長さを設定　マスのサイズは外部から設定
		float collLength = 100 * searchCollCell;

		//縦横のコライダーの設定
		searchCollHori = AddComponent<BoxCollider2D>();
		searchCollHori->SetSize({ collLength, searchCollThickness, 0.f });
		searchCollHori->SetGameObject(this);
		searchCollHori->SetIsTrigger(true);

		searchCollVert = AddComponent<BoxCollider2D>();
		searchCollVert->SetSize({ searchCollThickness, collLength, 0.f });
		searchCollHori->SetGameObject(this);
		searchCollHori->SetIsTrigger(true);
	}
}

void ConnectObject::Update()
{
	//全ての攻撃判定オブジェクトのアクティブ状態をリセット
	ResetAttackObjectsActive();


	//他の連結ブロックと繋がっているか検知し、接触している場合は攻撃判定を追加する
	SearchConnectedState();

	//デバッグ用の座標移動
	debug_Move();

}

void ConnectObject::ResetAttackObjectsActive()
{
	for (GameObject2D* obj : emitAttackObjects)
	{
		//SpriteRenderer* renderer = 

		obj->GetComponent<SpriteRenderer>()->SetIsActive(false);
		obj->GetComponent<BoxCollider2D>()->SetIsActive(false);
		obj->SetIsActive(false);
	}
}

void ConnectObject::SearchConnectedState()
{
	//自分より大きい番号の座標を保存する配列
	std::vector<hft::HFFLOAT3> connectTfmArray;

	//連結オブジェクトがある場合、自分の番号より大きいかを確認
	for (ConnectObject* obj : connectObjArray)
	{
		if (myInstanceNumber < obj->GetInstanceNumber())
		{
			//大きい場合は座標を保存する
			hft::HFFLOAT3 pos = obj->GetTransform().position;
			connectTfmArray.push_back(pos);
		}
	}

	//連結している座標が無い場合は何もしない
	if (connectTfmArray.empty()) { return; }


	//同じ向きで複数個連結している時の判定被り防止処理
	//同じ向きで連結している座標がある場合は距離が遠い方を配列から除外

	std::vector<hft::HFFLOAT3> connectDirArray;
	hft::HFFLOAT3 myPos = GetComponent<Transform>()->position;
	
	//削除する要素番号にtrueを付ける
	std::vector<bool> deleteIdx(connectTfmArray.size(), false);

	for (int trfIdx = 0; trfIdx < connectTfmArray.size(); trfIdx++)
	{
		//今の座標がどの向きに繋がっているか確認
		hft::HFFLOAT3 curdir = GetConnectionAxis(myPos, connectTfmArray[trfIdx]);

		//同じ向きで繋がっている他の座標があるか確認
		auto it = std::find_if(
			connectDirArray.begin(),
			connectDirArray.end(),
			[&](const hft::HFFLOAT3& v)
			{
				return v.x == curdir.x && v.y == curdir.y;
			}
		);
		if (it != connectDirArray.end())
		{
			//ある場合は今参照している座標との距離を測る
			int sameDirIndex = std::distance(connectDirArray.begin(), it);
			
			hft::HFFLOAT3 curIndexDiff  = myPos - connectTfmArray[trfIdx];
			hft::HFFLOAT3 sameIndexDiff = myPos - connectTfmArray[sameDirIndex];

			float curIndexDis = sqrtf(curIndexDiff.x * curIndexDiff.x + curIndexDiff.y * curIndexDiff.y);

			float sameIndexDis = sqrtf(sameIndexDiff.x * sameIndexDiff.x + sameIndexDiff.y * sameIndexDiff.y);
			
			//遠い距離の方の要素番号を消すフラグを立てる
			if (curIndexDis > sameIndexDis)
			{
				deleteIdx[trfIdx] = true;
			}
			else
			{
				deleteIdx[sameDirIndex] = true;
			}
		}
		else
		{
			//ない場合は向きだけ保存して次の座標に
			connectDirArray.push_back(curdir);
		}
	}

	//削除する要素番号に該当する座標を消去
	//一時保存用の配列を作り、削除フラグがfalseの要素番号だけ中身を取得
	//取得した一時保存配列の中身を入れ替える
	std::vector<hft::HFFLOAT3> tmpArray;
	for (int i = 0; i < deleteIdx.size(); i++)
	{
		if (!deleteIdx[i])
		{
			hft::HFFLOAT3 savedPos = connectTfmArray[i];
			tmpArray.push_back(savedPos);
		}
	}
	connectTfmArray.swap(tmpArray);


	//残った座標の配列と自身の座標の間に攻撃判定を作る
	for (hft::HFFLOAT3 tarPos : connectTfmArray)
	{
		EmitAttackAtConnection(tarPos);
	}
}

void ConnectObject::EmitAttackAtConnection(const hft::HFFLOAT3 tarPos)
{
	//自身の座標
	hft::HFFLOAT3 myPos = GetComponent<Transform>()->position; 

	//自身の座標からどの向きに繋がっているか
	hft::HFFLOAT3 connectDir = GetConnectionAxis(myPos, tarPos);

	//間のマス数
	int connectCellCount = GetContactTileDistance(myPos, tarPos, 100.f);

	//間のオブジェクトを生成
	SpawnAttackObjects(myPos, connectDir, connectCellCount, 100.f);
}


hft::HFFLOAT3 ConnectObject::GetConnectionAxis(hft::HFFLOAT3 originPos, hft::HFFLOAT3 tarPos)
{
	hft::HFFLOAT3 dir = tarPos - originPos;	//自分からターゲットまでの向き

	//縦と横どちらに大きく傾いているか特定
	if (fabsf(dir.x) > fabsf(dir.y))
	{
		//左右
		return (dir.x > 0.0f)
			? hft::HFFLOAT3{ 1.0f, 0.0f, 0.0f }
			: hft::HFFLOAT3{ -1.0f, 0.0f, 0.0f };
	}
	else
	{
		//上下
		return (dir.y > 0.0f)
			? hft::HFFLOAT3{ 0.0f, 1.0f, 0.0f }
			: hft::HFFLOAT3{ 0.0f, -1.0f, 0.0f };
	}
}

int ConnectObject::GetContactTileDistance(hft::HFFLOAT3 originPos, hft::HFFLOAT3 tarPos, float cellSize)
{
	hft::HFFLOAT3 dir = tarPos - originPos;	//自分からターゲットまでの向き
	float emptyLength = sqrtf(dir.x * dir.x + dir.y * dir.y);

	return (int)(emptyLength / cellSize);
}

void ConnectObject::SpawnAttackObjects(hft::HFFLOAT3 originPos, hft::HFFLOAT3 connectDir, int cellCount,float cellSize)
{
	//1マス配置ごとの座標の移動量
	hft::HFFLOAT3 tileStep = connectDir * cellSize;

	//オブジェクトの生成位置。初期値は自身の位置から1マス分進んだところ
	hft::HFFLOAT3 spawnPos = originPos + tileStep;

	//自身の座標から接触相手の座標まで攻撃判定用オブジェクトを配置する
	for (int i = 0; i < cellCount - 1; i++)
	{
		//連結部分ののマスの数が今持っている配列より多ければ新しく追加
		if (emitAttackObjects.size() <= i)
		{
			GameObject2D* attackObj = new GameObject2D;
			attackObj->Init();

			//レンダラーの設定
			SpriteRenderer* renderer = attackObj->AddComponent<SpriteRenderer>();
			renderer->LoadTexture("Assets/01-Texture/99-Test/char01.png");

			//コライダーの設定(横長)
			BoxCollider2D* boxColl2D = attackObj->AddComponent<BoxCollider2D>();
			boxColl2D->SetSize(hft::HFFLOAT3{ cellSize, cellSize, 0.f } );

			//位置の設定
			Transform* trf = attackObj->GetTransformPtr();
			trf->position = spawnPos;
			trf->scale = hft::HFFLOAT3{ cellSize, cellSize, 0.f };

			emitAttackObjects.push_back(attackObj);
		}
		else
		{
			//それ以下ならオブジェクトをアクティブ状態にし、位置を調整する
			emitAttackObjects[i]->SetIsActive(true);
			emitAttackObjects[i]->GetTransformPtr()->position = spawnPos;
		}

		//生成位置を次のマスに移動させる
		spawnPos += tileStep;
	}
}



/**
* @brief	コライダー同士が衝突した際の処理
* @param	Collider2D*	_p_col	2D用コライダーのポインタ
*/
void ConnectObject::OnCollisionEnter(Collider* _p_col) 
{
	//接触相手が自分以外の連結ブロックかつ、相手の本体のコライダーの場合は接触している判定
	if (GameObject* obj = _p_col->GetGameObject())
	{
		ConnectObject* connectObj = dynamic_cast<ConnectObject*>(obj);

		if (connectObj && connectObj != this && _p_col == connectObj->GetBodyCollider())
		{
			std::cout << connectObj->GetInstanceNumber() << "番目のオブジェクトが接触" << std::endl;

			//既に取得した連結ブロックと重複しているか確認
			auto it = std::find(connectObjArray.begin(), connectObjArray.end(), connectObj);

			if (it == connectObjArray.end())
			{
				connectObjArray.push_back(connectObj);
			}
		}
	}
}
/**
* @brief	コライダー同士が離れた際の処理
* @param	Collider2D*	_p_col	2D用コライダーのポインタ
*/
void ConnectObject::OnCollisionExit(Collider* _p_col)
{
	//接触相手が自分以外の連結ブロックかつ、相手の本体のコライダーの場合は接触している判定
	if (GameObject* obj = _p_col->GetGameObject())
	{
		ConnectObject* connectObj = dynamic_cast<ConnectObject*>(obj);

		if (connectObj && connectObj != this && _p_col == connectObj->GetBodyCollider())
		{
			std::cout << connectObj->GetInstanceNumber() << "番目のオブジェクトが離れた" << std::endl;

			//既に取得した連結ブロックと重複しているか確認
			auto it = std::find( connectObjArray.begin(), connectObjArray.end(), connectObj);

			if (it != connectObjArray.end())
			{
				connectObjArray.erase(it);
			}
		}
	}
}


/**
* @brief	コライダー同士が接触中の処理
* @param	Collider2D*	_p_col	2D用コライダーのポインタ
*/
void ConnectObject::OnCollisionStay(Collider* _p_col) 
{
	
}

void ConnectObject::debug_Move()
{
	GetComponent<Transform>()->position += debug_moveDir;

	hft::HFFLOAT3 dir = debug_startPos - GetComponent<Transform>()->position;
	float length = sqrtf(dir.x * dir.x + dir.y * dir.y);

	if (length > 1920)
	{
		GetComponent<Transform>()->position = debug_startPos;
	}
}
