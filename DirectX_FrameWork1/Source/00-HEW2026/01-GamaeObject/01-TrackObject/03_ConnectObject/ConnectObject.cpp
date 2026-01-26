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

	searchCollCell = ConnectObjectParam::searchCollCellCount;

	bodyCollider = nullptr;
	searchCollVert = nullptr;
	searchCollHori = nullptr;
}

void ConnectObject::Init()
{
	//本体部分の設定
	{
		p_transform->scale = ConnectObjectParam::mainBodyScale;

		//スプライトレンダラー
		const char* texName = ConnectObjectParam::mainBodyTexName;
		std::shared_ptr<Texture> tex = GetComponent<SpriteRenderer>()->LoadTexture(texName);

		//コライダー
		bodyCollider = AddComponent<BoxCollider2D>();
	}


	//縦横の審査用コライダーの設定
	{
		//長さを設定　マスのサイズは外部から設定
		float collLength = ConnectObjectParam::searchCollCellSize * searchCollCell;

		//縦横のコライダーの設定
		searchCollHori = AddComponent<BoxCollider2D>();
		searchCollHori->SetSize({ collLength, searchCollThickness, 0.f });
		searchCollHori->SetGameObject(this);
		searchCollHori->SetIsTrigger(true);

		searchCollVert = AddComponent<BoxCollider2D>();
		searchCollVert->SetSize({ searchCollThickness, collLength, 0.f });
		searchCollVert->SetGameObject(this);
		searchCollVert->SetIsTrigger(true);
	}
}

void ConnectObject::Update()
{
	//全ての攻撃判定オブジェクトのアクティブ状態をリセット
	ResetAttackObjectsActive();

	//他の連結ブロックと繋がっているか検知し、接触している場合は攻撃判定を追加する
	SearchConnectedState();

	//デバッグ用の座標移動
	//debug_Move();
}

void ConnectObject::ResetAttackObjectsActive()
{
	for (GameObject2D* obj : emitAttackObjects)
	{
		obj->SetIsActive(false);
		obj->SetIsRender(false);
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
	if (connectTfmArray.empty()) 
	{
		return; 
	}


	//同じ向きで複数個連結している時の判定被り防止処理
	//同じ向きで連結している座標がある場合は距離が遠い方を配列から除外
	
	//連結方向を保存する配列
	std::vector<hft::HFFLOAT3> connectDirArray;

	//連結方向の配列番号を保持する配列
	std::vector<int> connectDirIndexArray;

	//自身の座標
	hft::HFFLOAT3 myPos = GetComponent<Transform>()->position;

	//連結相手の座標の内、攻撃判定設置に使わない座標の削除フラグ
	std::vector<bool> deleteIdx(connectTfmArray.size(), false);


	//連結相手の全ての接触方向を調べる
	//同じ方向に複数接触していた場合、自身からより近い座標のみ保存する
	for (int trfIdx = 0; trfIdx < connectTfmArray.size(); trfIdx++)
	{
		//現在調べている座標の接触方向
		hft::HFFLOAT3 curdir = GetConnectionAxis(myPos, connectTfmArray[trfIdx]);

		//同じ連結方向が今の配列内にあるか確認、ない場合は最後尾の次の要素を入れたままにする
		auto connectDirIt = connectDirArray.end();

		for (auto curIt = connectDirArray.begin(); curIt != connectDirArray.end(); curIt++)
		{
			if (curIt->x == curdir.x && curIt->y == curdir.y)
			{
				//方向が同じ場合はイテレータ代入
				connectDirIt = curIt;
				break;
			}
		}

		//同じ方向があった場合、自身からより遠い座標を消す
		if (connectDirIt != connectDirArray.end())
		{
			//既に座標の要素番号
			int dirIdx = std::distance(connectDirArray.begin(), connectDirIt);
			int sameTfmIdx = connectDirIndexArray[dirIdx];

			hft::HFFLOAT3 curDiff = myPos - connectTfmArray[trfIdx];
			hft::HFFLOAT3 sameDiff = myPos - connectTfmArray[sameTfmIdx];

			float curDistSq = curDiff.x * curDiff.x + curDiff.y * curDiff.y;
			float sameDistSq = sameDiff.x * sameDiff.x + sameDiff.y * sameDiff.y;

			if (curDistSq > sameDistSq)
			{
				deleteIdx[trfIdx] = true;
			}
			else
			{
				deleteIdx[sameTfmIdx] = true;
				connectDirIndexArray[dirIdx] = trfIdx;
			}
		}
		else
		{
			//同じ方向が無かった場合、向きと要素番号を保存して次の座標を調べる
			connectDirArray.push_back(curdir);
			connectDirIndexArray.push_back(trfIdx);
		}
	}


	//削除する要素番号に該当する座標を消去
	std::vector<hft::HFFLOAT3> tmpArray;
	for (int i = 0; i < deleteIdx.size(); i++)
	{
		if (!deleteIdx[i])
		{
			//削除フラグがfalseの要素番号だけ中身を取得
			hft::HFFLOAT3 savedPos = connectTfmArray[i];
			tmpArray.push_back(savedPos);
		}
	}

	//取得した一時保存配列の中身を入れ替える
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

	SpawnAttackObjects(tarPos, connectDir);
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
	hft::HFFLOAT3 dir = tarPos - originPos;
	hft::HFFLOAT3 connectDir = GetConnectionAxis(originPos, tarPos);

	//浮動小数点の誤差を考慮して四捨五入
	float distance;
	if (connectDir.x != 0.0f) 
	{
		distance = fabsf(dir.x) / cellSize;
	}
	else 
	{
		distance = fabsf(dir.y) / cellSize;
	}

	//0.5を足して四捨五入。整数に近い値にする
	return static_cast<int>(distance + 0.5f);
}


float ConnectObject::GetContactDistance(hft::HFFLOAT3 originPos, hft::HFFLOAT3 tarPos)
{
	hft::HFFLOAT3 dir = tarPos - originPos;
	hft::HFFLOAT3 connectDir = GetConnectionAxis(originPos, tarPos);

	//浮動小数点の誤差を考慮して四捨五入
	float distance;
	if (connectDir.x != 0.0f)
	{
		distance = dir.x;
	}
	else
	{
		distance = dir.y;
	}

	return distance;
}

void ConnectObject::SpawnAttackObjects(hft::HFFLOAT3 originPos, hft::HFFLOAT3 connectDir, int cellCount,float cellSize)
{
	//1マス配置ごとの座標の移動量
	hft::HFFLOAT3 tileStep = connectDir * cellSize;

	//オブジェクトの生成位置。初期値は自身の位置から1マス分進んだところ
	hft::HFFLOAT3 spawnPos = originPos + tileStep;
	spawnPos.z = -1;

	//表示する画像の向き、縦と横の向きを切り替える
	hft::HFFLOAT3 texRotation = ConnectObjectParam::emitAttackVertRotation;
	if (connectDir.y <= 0) { texRotation = ConnectObjectParam::emitAttackHoriRotation; }

	//自身の座標から接触相手の座標までの間のマスに攻撃判定用オブジェクトを配置する
	for (int i = 0; i < cellCount - 1; i++)
	{
		GameObject2D* attackObj = nullptr;
		bool foundUnused = false;

		//既存の配列の中から非アクティブなものを探す
		for (GameObject2D* obj : emitAttackObjects)
		{
			//オブジェクトのisActiveフラグがいじれないのでコンポーネントのフラグでアクティブ状態を確認
			if (!obj->GetTransform().GetIsActive())
			{
				//ある場合はそれを生成位置に持ってくる
				attackObj = obj;
				foundUnused = true;
				break;
			}
		}

		//配列内から見つからなければ新規作成
		if (!foundUnused)
		{
			attackObj = new GameObject2D;
			attackObj->Init();

			//レンダラーの設定
			SpriteRenderer* renderer = attackObj->GetComponent<SpriteRenderer>();
			const char* texName = ConnectObjectParam::emitAttackTexName;
			renderer->LoadTexture(texName);

			//コライダーの設定
			BoxCollider2D* boxColl2D = attackObj->AddComponent<BoxCollider2D>();
			boxColl2D->SetSize(hft::HFFLOAT3{ cellSize, cellSize, 0.f });

			emitAttackObjects.push_back(attackObj);
			std::cout << "攻撃判定オブジェクトを新しく生成" << std::endl;
		}
		else
		{
			std::cout << "攻撃判定オブジェクトを再利用" << std::endl;
		}

		//オブジェクトをアクティブにして位置と回転を設定
		attackObj->SetIsActive(true);
		attackObj->SetIsRender(true);

		Transform* trf = attackObj->GetTransformPtr();
		trf->position = spawnPos;
		trf->scale = hft::HFFLOAT3{ cellSize, cellSize, 0.f };
		trf->rotation = texRotation;


		//生成位置を次のマスに移動させる
		spawnPos += tileStep;
	}
}


void ConnectObject::SpawnAttackObjects(hft::HFFLOAT3 tarPos, hft::HFFLOAT3 connectDir)
{

	//表示する画像の向き、縦と横の向きを切り替える
	hft::HFFLOAT3 texRotation = ConnectObjectParam::emitAttackHoriRotation;
	if (connectDir.y <= 0)
	{
		texRotation = ConnectObjectParam::emitAttackVertRotation;
	}

	//自身の位置
	hft::HFFLOAT3 myPos = GetTransform().position;
	
	//距離を計る
	float distance = GetContactDistance(myPos, tarPos);
	
	//オブジェクトの生成位置を計る
	float middleDistance = distance / 2;
	hft::HFFLOAT3 spawnPos = myPos + (connectDir * middleDistance);
	spawnPos.z = -4;

	//コライダーのサイズを設定
	float collThickness = ConnectObjectParam::emitAttackCollThickness;
	hft::HFFLOAT3 collSize = { collThickness, distance, 0.f};
	if (connectDir.y <= 0)
	{
		collSize = { distance, collThickness, 0.f};
	}

	//テクスチャのサイズを設定
	float texThickNess = ConnectObjectParam::emitAttacktTexThickness;
	hft::HFFLOAT3 texSize = { texThickNess, distance, 0.f };
	if (connectDir.y <= 0)
	{
		texSize = { distance, texThickNess, 0.f };
	}


	//自身の座標から接触相手の座標までの間のマスに攻撃判定用オブジェクトを配置する
	GameObject2D* attackObj = nullptr;
	bool foundUnused = false;

	//既存の配列の中から非アクティブなものを探す
	for (GameObject2D* obj : emitAttackObjects)
	{
		if (!obj->GetTransform().GetIsActive())
		{
			//ある場合はそのオブジェクトを使う
			attackObj = obj;
			foundUnused = true;
			break;
		}
	}

	//配列内から見つからなければ新規作成して配列に格納
	if (!foundUnused)
	{
		attackObj = new GameObject2D;
		attackObj->Init();
		attackObj->SetTag("Enemy");
		attackObj->GetComponent<SpriteRenderer>()->LoadTexture(ConnectObjectParam::emitAttackTexName);
		attackObj->AddComponent<BoxCollider2D>();
		emitAttackObjects.push_back(attackObj);
	}
	
	//アクティブ化
	attackObj->SetIsActive(true);
	attackObj->SetIsRender(true);

	//位置、サイズ、回転角度、タグの設定
	attackObj->GetTransformPtr()->position = spawnPos;
	attackObj->GetTransformPtr()->scale	   = texSize;
	attackObj->GetTransformPtr()->rotation = texRotation;

	//コライダーのサイズの設定
	attackObj->GetComponent<BoxCollider2D>()->SetSize(collSize);
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

//void ConnectObject::debug_Move()
//{
//	GetComponent<Transform>()->position += debug_moveDir;
//
//	hft::HFFLOAT3 dir = debug_startPos - GetComponent<Transform>()->position;
//	float length = sqrtf(dir.x * dir.x + dir.y * dir.y);
//
//	if (length > 500)
//	{
//		GetComponent<Transform>()->position = debug_startPos;
//	}
//}
