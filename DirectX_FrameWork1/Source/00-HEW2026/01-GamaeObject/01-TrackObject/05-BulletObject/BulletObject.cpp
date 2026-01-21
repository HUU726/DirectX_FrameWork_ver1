// 弾オブジェクト::タグ:Object

#include"BulletObject.h"
#include"BulletObjectParam.h"
#include"../../../../00-HEW2026/10-Map/00-BaseMap/BaseMap.h"
#include "../../../../99-Lib/01-MyLib/07-Component/06-Animator/01-SpriteAnimator/SpriteAnimator.h"
#include "../../../../99-Lib/01-MyLib/07-Component/02-Renderer/01-SpriteRenderer/SpriteRenderer.h"

#define RIGHT 0
#define UP 1
#define LEFT 2
#define DOWN 3

//=================================================================
//Init
//=================================================================
void BulletObject::Init(const int& NewDirection)
{
	tag = BulletObjectParam::tag;
	p_transform->scale = BulletObjectParam::scale;
	auto col = AddComponent<BoxCollider2D>();
	col->SetIsActive(false);
	SetIsActive(false);
	
	// マップの枠の数値を入れる
	LeftTop = { -250.f,250.f };
	RightBottom= { 250.f,-250.f };
	//LeftTop = GetComponent<BaseMap>()->GetLefTopPos();
	//RightBottom = GetComponent<BaseMap>()->GetRitBotPos();
	

	// 方向の情報
	SetDirection(NewDirection);
	
	// 当たり判定初期化
	
	// アニメーター初期化
	// // ① 先に追加する
	SpriteRenderer* renderer = AddComponent<SpriteRenderer>();
	if (!renderer)
	{
		std::cout << "SpriteRenderer 追加失敗\n";
		return;
	}

	//画像の設定
	{
		//レンダラーの設定
		GetComponent<SpriteRenderer>()->LoadTexture(BulletObjectParam::BulletObjTexName);

		//アニメーターの設定
		SpriteAnimator* p_spriteAnimator = AddComponent<SpriteAnimator>(hft::HFFLOAT2(1, 1));
		hft::HFFLOAT2 div = p_spriteAnimator->GetDivision();


		//animationの設定
		// 通常
		SpriteAnimation anim1(div, { 0,0 }, 1);
		anim1.InActive();
		anim1.SetID(0);

		anim1.SetType(SPRITE_ANIM_TYPE::LOOP);
		anim1.SetPriority(0);
		float flame = 1;

		for (int i = 0; i < 1; i++)
		{
			anim1.GetCellRef(i).flame = flame;
		}
		p_spriteAnimator->AddAnimation(anim1);

		// 破裂
		SpriteAnimation anim2(div, { 0,0 }, 1);
		anim2.InActive();
		anim2.SetID(1);

		anim2.SetType(SPRITE_ANIM_TYPE::NORMAL);
		anim2.SetPriority(0);
		flame = 1;

		for (int i = 0; i < 1; i++)
		{
			anim2.GetCellRef(i).flame = flame;
		}

		p_spriteAnimator->AddAnimation(anim2);
	}
	std::cout << "弾調整完了\n";
}

//=======================================================================
//Update
//=======================================================================
void BulletObject::Update()
{
	// 弾が存在するとき
	if (!active)return;

	switch (GetDirection()) {
	case 0:p_transform->position.x += 5.0f; break;
	case 1:p_transform->position.y += 5.0f; break;
	case 2:p_transform->position.x -= 5.0f; break;
	case 3:p_transform->position.y -= 5.0f; break;
	}
}

//===============================================================================================
// フレーム数を超えるまで座標を更新し、フレーム数を超過した場合Blastへ移行する
//===============================================================================================
/*
void BulletObject::Defoult()
{
	GetComponent<BoxCollider2D>()->SetIsActive(true);	// 当たり判定をアクティブ
	GetComponent<SpriteAnimator>()->Play(0);
	if (timer < livetime)
	{
		UpdatePos();		// 座標更新
		CheakMyPos();		// マップの枠から出ないかチェック
	}
	else
	{
		timer = 0;	// フレーム数リセット
		currentState = BulletObject::blast;	// 状態を移行
	}
}
*/

//===============================================================================================
// フレーム数を超過した場合、初期化しする
//===============================================================================================
/*
void BulletObject::Blast()
{
	GetComponent<SpriteAnimator>()->Stop(0);
	GetComponent<SpriteAnimator>()->Play(1);
	std::cout << "弾オブジェクト破裂アニメーション\n";
	GetComponent<BoxCollider2D>()->SetIsActive(false);	// 当たり判定を非アクティブ
	if (timer > blasttime)
	{
		currentState = BulletObject::defoult;
		timer = 0;
		SetBulletActive(false);
		std::cout << "弾オブジェクトを消滅\n";
	}
}
*/

//===============================================================================================
// 方向別に座標を更新させる (右向きなら右方向へ座標を更新、上向きなら上方向へ座標を更新..)
//===============================================================================================
/*
void BulletObject::UpdatePos()
{
	// 今の弾オブジェクトの座標取得
	const hft::HFFLOAT3 NowPos = p_transform->position;

	switch (GetDirection())
	{
	case RIGHT:
		p_transform->position.x = NowPos.x + spead * 1.0f; 
		std::cout << "右方向に更新\n";
		break;
	case UP:
		 p_transform->position.y = NowPos.y + spead * 1.0f; 
		 std::cout << "上方向に更新\n";
		break;
	case LEFT:
		p_transform->position.x = NowPos.x - spead * 1.0f; 
		std::cout << "左方向に更新\n";
		break;
	case DOWN:
		p_transform->position.y = NowPos.y - spead * 1.0f; 
		std::cout << "下方向に更新\n";
		break;
	default:
		std::cout << "弾オブジェクト座標更新エラー\n";
	}
}
*/
//================================================================================================
// 方向別にマップの枠組みから出ないようにする(上方向ならTopと比較、右方向ならRightと比較..)
//================================================================================================
/*
void BulletObject::CheakMyPos()
{
	// 枠組みから超えるようなら反対側の座標を代入する
	switch (GetDirection())
	{
	case RIGHT:
		if (RightBottom.x < (p_transform->position.x)) { this->p_transform->position.x = LeftTop.x; std::cout << "ワープ\n"; }
		break;
	case UP:
		if (LeftTop.y < (p_transform->position.y)) { this->p_transform->position.y = RightBottom.y; std::cout << "ワープ\n"; }
		break;
	case LEFT:
		if (LeftTop.x > (p_transform->position.x)) { this->p_transform->position.x = RightBottom.x; std::cout << "ワープ\n"; }
		break;
	case DOWN:
		if (RightBottom.y > (p_transform->position.y)) { this->p_transform->position.y = LeftTop.y; std::cout << "ワープ\n"; }
		break;
	default:
		std::cout << "座標チェックエラー\n";
	}
}
*/
//==================================================================================================
// OnCollisionEnterの処理
//==================================================================================================
void BulletObject::OnCollisionEnter(Collider* _p_col)
{
	if (!_p_col)return;
	GameObject* hit = _p_col->GetGameObject();
	if (!hit)return;
	if (hit == owner)return;
	SetBulletActive(false);
	/*
	GameObject* col = _p_col->GetGameObject();
	// 対象のオブジェクトにヒットした際、blastに移行
	if (col->GetTag() == "Enemy" || col->GetTag() == "Player")
	{
		std::cout << "弾オブジェクトが何かにヒット\n";
		currentState = blast;
	}*/
}