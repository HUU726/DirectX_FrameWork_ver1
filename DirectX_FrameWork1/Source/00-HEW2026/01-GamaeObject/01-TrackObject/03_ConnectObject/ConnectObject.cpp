#include "ConnectObject.h"
#include "ConnectObjectParam.h"

#include "DirectX_FrameWork1/Source/99-Lib/01-MyLib/07-Component/03-Collider/01-Collider2D/BoxCollider2D.h"

#include "../../../../99-Lib/01-MyLib/07-Component/06-Animator/01-SpriteAnimator/SpriteAnimator.h"
#include "../../../../99-Lib/01-MyLib/07-Component/02-Renderer/01-SpriteRenderer/SpriteRenderer.h"

int ConnectObject::instanceCounter = 0;

ConnectObject::ConnectObject()
{
	//生成
	instanceCounter++;
	myInstanceNumber = instanceCounter;

	searchCollCell = ConnectObjectParam::searchCollCell;

	searchCollVert = nullptr;
	searchCollHori = nullptr;
}

void ConnectObject::Init()
{
	//本体部分の設定
	{
		p_transform->position = hft::HFFLOAT3{ 0.f,0.f, 0.f };
		p_transform->scale = hft::HFFLOAT3{ 100.f,100.f,1 };

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

		AddComponent<BoxCollider2D>();
	}


	//縦横の審査用コライダーの設定
	{
		//長さを設定　マスのサイズは外部から設定
		float collLength = 100 * searchCollCell;

		//縦横のコライダーの設定
		searchCollHori = AddComponent<BoxCollider2D>();
		searchCollHori->SetIsTrigger(true);
		searchCollHori->SetSize({ collLength, searchCollThickness, 0.f });

		searchCollVert = AddComponent<BoxCollider2D>();
		searchCollVert->SetIsTrigger(true);
		searchCollVert->SetSize({ searchCollThickness, collLength, 0.f });
	}
}

void ConnectObject::Update()
{
	//他の連結ブロックと繋がっているか検知し、接触している場合は攻撃判定を追加する


	OnCollisionEnter2D(searchCollHori);

}

bool ConnectObject::SearchConnectedState()
{
	//接触相手のコライダーから、自身以外の連結オブジェクトがあるかを検索する

	//接触した連結オブジェクト配列
	std::vector<ConnectObject*> connectObjArray;

	//自分より大きい番号の座標を保存する配列
	std::vector<hft::HFFLOAT3> connectTfmArray;

	//連結オブジェクトがある場合、自分の番号より大きいかを確認
	for (ConnectObject* obj : connectObjArray)
	{
		if (instanceCounter < obj->GetInstanceNumber())
		{
			//大きい場合は座標を保存する
			hft::HFFLOAT3 pos = obj->GetTransform().position;

			connectTfmArray.push_back(pos);
		}
	}

	//保存した座標と自身の座標の間に攻撃判定を作る
	for (hft::HFFLOAT3 tarPos : connectTfmArray)
	{
		EmitAttackAtConnection(tarPos);
	}


	return false;
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
	for (int i = 0; i <= cellCount - 1; i++)
	{
		//連結部分ののマスの数が今持っている配列より多ければ新しく追加
		if (emitAttackObjects.size() < i)
		{
			GameObject2D* attackObj = new GameObject2D;
			attackObj->Init();

			//レンダラーの設定
			SpriteRenderer* renderer = attackObj->AddComponent<SpriteRenderer>();
			renderer->LoadTexture("Assets/01-Texture/99-Test/char01.png");

			//コライダーの設定(横長)
			BoxCollider2D* boxColl2D = AddComponent<BoxCollider2D>();
			float size = ConnectObjectParam::searchCollThickness;
			boxColl2D->SetSize(hft::HFFLOAT3{ cellSize, size, 0.f } );

			//位置の設定
			Transform* trf = attackObj->GetTransformPtr();
			trf->position = spawnPos;
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

void ConnectObject::OnCollisionEnter2D(Collider2D* _p_col)
{

}

void ConnectObject::OnCollisionExit2D(Collider2D* _p_col)
{

}

void ConnectObject::OnCollisionStay2D(Collider2D* _p_col)
{

}

void ConnectObject::OnTriggerEnter2D(Collider2D* _p_col)
{

}

void ConnectObject::OnTriggerExit2D(Collider2D* _p_col)
{
	//_p_col->OnCollisionEnter();
}

void ConnectObject::OnTriggerStay2D(Collider2D* _p_col)
{

}


