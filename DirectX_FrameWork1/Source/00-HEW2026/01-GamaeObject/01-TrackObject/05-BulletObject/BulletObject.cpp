// 弾オブジェクト::タグ:Bullet

// 当たり判定,ワープ

#include"BulletObject.h"
#include"BulletObjectParam.h"
#include "../../../../99-Lib/01-MyLib/07-Component/06-Animator/01-SpriteAnimator/SpriteAnimator.h"
#include "../../../../99-Lib/01-MyLib/07-Component/02-Renderer/01-SpriteRenderer/SpriteRenderer.h"

#define RIGHT 0
#define UP 1
#define LEFT 2
#define DOWN 3


//=================================================================
//Init
//=================================================================
void BulletObject::Init(BaseMap* New_p_map, BoxCollider2D* my_owner, const int& NewDirection)
{
	SetTag(BulletObjectParam::tag);
	auto col = AddComponent<BoxCollider2D>();
	col->SetIsActive(false);
	SetIsActive(false);
	timer = 0;
	active = BulletObjectParam::active;
	livetime = BulletObjectParam::livetime;
	spead = BulletObjectParam::spead;
	blasttime = BulletObjectParam::blasttime;
	startScene = BulletObjectParam::startScene;
	NotHittime = BulletObjectParam::NotHittime;
	_owner = my_owner;
	p_map = New_p_map;

	// マップから情報を受け取る
	//LeftTop = { -250.f,250.f };
	//RightBottom= { 250.f,-250.f };
	LeftTop = p_map->GetLefTopPos();		// マップの端の数値(左と上)
	RightBottom = p_map->GetRitBotPos();	// マップの端の数値(右と下)
	float map_scele = p_map->GetScaleRatio();	// マップの大きさに合わせるためのレート(scaleに掛ける)

	// サイズ更新(マップサイズに合わせたサイズにする)
	p_transform->scale.x *= map_scele;
	p_transform->scale.y *= map_scele;
	p_transform->scale.z *= map_scele;

	// 方向の情報
	SetDirection(NewDirection);

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
	if (GetBulletActive())
	{
		timer++;
		switch (currentState) {
		case defoult:Defoult(); break;
		case blast:Blast(); break;
		}
	}
}

//===============================================================================================
// フレーム数を超えるまで座標を更新し、フレーム数を超過した場合Blastへ移行する
//===============================================================================================
void BulletObject::Defoult()
{
	std::cout << "Bullet出現\n";
	if (startScene == true)
	{
		startScene = false;
		GetComponent<BoxCollider2D>()->SetIsActive(true);	// 当たり判定をアクティブ
		GetComponent<SpriteRenderer>()->SetIsActive(true);
		GetComponent<SpriteAnimator>()->Play(0);
	}

	if (timer <= livetime)
	{
		UpdatePos();										// 座標更新
		CheakMyPos();										// マップの枠から出ないかチェック
	}
	if (timer > livetime)
	{
		timer = 0;											// フレーム数リセット
		startScene = true;
		currentState = BulletObject::blast;					// 状態を移行
	}
}


//===============================================================================================
// フレーム数を超過した場合、初期化する
//===============================================================================================
void BulletObject::Blast()
{
	if (startScene == true)
	{
		startScene = false;
		GetComponent<SpriteAnimator>()->Stop(0);
		GetComponent<SpriteRenderer>()->SetIsActive(false);
		std::cout << "弾オブジェクト破裂アニメーション\n";
		GetComponent<BoxCollider2D>()->SetIsActive(false);	// 当たり判定を非アクティブ
	}
	if (timer >= blasttime)
	{
		startScene = true;
		currentState = BulletObject::defoult;
		timer = 0;
		SetBulletActive(false);
		std::cout << "弾オブジェクトを消滅\n";
	}
}

//===============================================================================================
// 方向別に座標を更新させる (右向きなら右方向へ座標を更新、上向きなら上方向へ座標を更新..)
//===============================================================================================
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

//================================================================================================
// 方向別にマップの枠組みから出ないようにする(上方向ならTopと比較、右方向ならRightと比較..)
//================================================================================================

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

//==================================================================================================
// OnCollisionEnterの処理
//==================================================================================================
void BulletObject::OnCollisionEnter(Collider* _p_col)
{
	GameObject* col = _p_col->GetGameObject();
	Collider* owner = _owner;
	// 対象のオブジェクトにヒットした際、blastに移行
	if (col->GetTag() == "Gun" || col->GetTag() == "Player" || col->GetTag() == "Bom" || col->GetTag() == "Thorn" || col->GetTag() == "Connect")
	{
		// 時間内であれば発射をしたエネミーを当たる標的に含めない
		if (/*_p_col == owner && */ NotHittime > 0)
		{

		}
		else
		{
			std::cout << "弾オブジェクトが何かにヒット\n";
		}
	}
}