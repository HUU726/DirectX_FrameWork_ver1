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


}

bool ConnectObject::SearchConnectedState()
{
	//接触相手のコライダーから、自身以外の連結オブジェクトがあるかを検索する

	//連結しているオブジェクトはこの配列に保管する
	std::vector<ConnectObject*> connectObj;

	//連結オブジェクトがある場合、自分の番号より大きいかを確認
	if(searchCollVert->GetSize)



	//大きい場合は座標を保存する


	//保存した座標と自身の座標の間に攻撃判定を作る

	return false;
}

void ConnectObject::EmitAttackAtConnection(const std::vector<Transform*> targetTrfArray)
{
	//縦と横、どちらの向きで繋がっているか確認する

	//接触相手の座標から自身の座標まで、何マス分あるか検知。マスのサイズは外部から指定する

	//自身を原点に、検知した向きに1マス分ずつ座標をずらしたところにオブジェクトを配置する
	//間のマス数が今アクティブな攻撃判定用オブジェクトより多い場合は追加でオブジェクトを生成する

	//
}


