// 弾オブジェクト::タグ:Bullet

#include"BulletObject.h"
#include"BulletObjectParam.h"
#include "../../../../99-Lib/01-MyLib/07-Component/06-Animator/01-SpriteAnimator/SpriteAnimator.h"
#include "../../../../99-Lib/01-MyLib/07-Component/02-Renderer/01-SpriteRenderer/SpriteRenderer.h"
#include"../02_ThornObject/ThormObject.h"
#include"../03_ConnectObject/ConnectObject.h"
#include"../04-Player/PlayerObject.h"
#include"../04_Enemy/BiteEnemy.h"
#include"../04_Enemy/GunEnemy.h"
#include"../04_Enemy/BombEnemy.h"

#define RIGHT 0
#define UP 1
#define LEFT 2
#define DOWN 3


//=================================================================
//Init(引数::BaseMap(マップの情報) , int(どの方向を向いているか))
//=================================================================
void BulletObject::Init(BaseMap* New_p_map,const int& NewDirection)
{
	
	timer = 0;									// タイマー初期化
	SetTag(BulletObjectParam::tag);				// タグの初期化
	active = BulletObjectParam::active;			// 弾が存在するか否か
	livetime = BulletObjectParam::livetime;		// 弾が画面にでている時間
	spead = BulletObjectParam::spead;			// 弾のスピード
	blasttime = BulletObjectParam::blasttime;	// 破裂してから消える時間
	startScene = BulletObjectParam::startScene;	// 開始時に一度だけ再生される
	NotHittime = BulletObjectParam::NotHittime;	// 発射時に本体に当たらない時間
	currentState = BulletObject::defoult;		// 最初にとる行動
	p_map = New_p_map;							// マップ情報の渡し

	// マップから情報を受け取る
	if (New_p_map == nullptr)
	{
		LeftTop = { -250.f,250.f };
		RightBottom = { 250.f,-250.f };
	}
	else
	{
		LeftTop = p_map->GetLefTopPos();		// マップの端の数値(左と上)
		RightBottom = p_map->GetRitBotPos();	// マップの端の数値(右と下)
		float map_scele = p_map->GetScaleRatio();	// マップの大きさに合わせるためのレート(scaleに掛ける)

		// サイズ更新(マップサイズに合わせたサイズにする)
		p_transform->scale.x *= map_scele;
		p_transform->scale.y *= map_scele;
		p_transform->scale.z *= map_scele;
	}

	// 方向の情報
	SetDirection(NewDirection);

	// 位置の設定
	{
		p_transform->scale = BulletObjectParam::scale;			// 大きさの初期化
		p_transform->position = BulletObjectParam::position;	// 座標の初期化
	}

	//画像の設定
	{
		//レンダラーの設定
		std::shared_ptr<Texture> tex = GetComponent<SpriteRenderer>()->LoadTexture(BulletObjectParam::BulletObjTexName);

		//アニメーターの設定
		SpriteAnimator* p_spriteAnimator = AddComponent<SpriteAnimator>(hft::HFFLOAT2(1, 1));
		hft::HFFLOAT2 div = p_spriteAnimator->GetDivision();

		//animationの設定
		// 通常
		SpriteAnimation anim1(div, { 0,0 }, 1);
		anim1.Active();
		anim1.SetID(0);
		anim1.SetType(SPRITE_ANIM_TYPE::NORMAL);
		anim1.SetPriority(0);
		float flame = 1;

		for (int i = 0; i < 1; i++)
		{
			anim1.GetCellRef(i).flame = flame;
		}
		p_spriteAnimator->AddAnimation(anim1);
	}
	//GetComponent<SpriteRenderer>()->SetIsActive(false);	// 初期化で描写しない

	// 本体のコライダー設定
	bodyCollider = AddComponent<BoxCollider2D>();
	bodyCollider->Init();
	hft::HFFLOAT3 p_size = p_transform->scale;			// サイズ分当たり判定をとる
	bodyCollider->SetSize(p_size);
	bodyCollider->SetIsActive(false);
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
		case defoult:Defoult(); break;		// 通常状態
		case blast:Blast(); break;			// 破裂状態
		}
	}
}

//===============================================================================================
// フレーム数を超えるまで座標を更新し、フレーム数を超過した場合Blastへ移行する
//===============================================================================================
void BulletObject::Defoult()
{
	if (startScene == true)
	{
		startScene = false;
		NotHittime = 10;
		GetComponent<BoxCollider2D>()->SetIsActive(true);	// 当たり判定をアクティブ
		GetComponent<SpriteRenderer>()->SetIsActive(true);	// 描写をする
		GetComponent<SpriteAnimator>()->Play(0);
	}
	if (timer <= livetime)
	{
		if (NotHittime > 0)
		{
			NotHittime--;// 発射直後の当たり判定を無効化
		}
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
		GetComponent<BoxCollider2D>()->SetIsActive(false);	// 当たり判定を非アクティブ
		NotHittime = 10;
	}
	if (timer >= blasttime)
	{
		startScene = true;
		currentState = BulletObject::defoult;
		timer = 0;
		SetBulletActive(false);
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
		//std::cout << "右方向に更新\n";
		break;
	case UP:
		 p_transform->position.y = NowPos.y + spead * 1.0f; 
		 //std::cout << "上方向に更新\n";
		break;
	case LEFT:
		p_transform->position.x = NowPos.x - spead * 1.0f; 
		//std::cout << "左方向に更新\n";
		break;
	case DOWN:
		p_transform->position.y = NowPos.y - spead * 1.0f; 
		//std::cout << "下方向に更新\n";
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
	// 相手の情報を取得
	GameObject* col = _p_col->GetGameObject();
	std::string tag = col->GetTag();
	TrackObject* player = dynamic_cast<PlayerObject*>(col);
	TrackObject* bite = dynamic_cast<BiteEnemy*>(col);
	TrackObject* gun = dynamic_cast<GunEnemy*>(col);
	TrackObject* bomb = dynamic_cast<BombEnemy*>(col);
	TrackObject* thorn = dynamic_cast<ThormObject*>(col);
	TrackObject* connect = dynamic_cast<ConnectObject*>(col);

	bool Hit = (player||bite || gun || bomb || thorn || connect);
	if (Hit == false)return;
	if (tag == "Gun" && NotHittime > 0)return;
	//	発射直後で無ければ,発射元に接触した場合消滅する
	currentState = BulletObject::blast;
	startScene = true;
}