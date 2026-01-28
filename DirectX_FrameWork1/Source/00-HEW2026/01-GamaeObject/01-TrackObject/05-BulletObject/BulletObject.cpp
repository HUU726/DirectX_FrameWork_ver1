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

// コンストラクタ
BulletObject::BulletObject()
{
	
}

//=================================================================
// 弾オブジェクトの初期化処理(引数::BaseMap(マップの情報) , int(どの方向を向いているか))
//=================================================================
void BulletObject::Init(BaseMap* New_p_map,const int& NewDirection)
{
	
	timer = 0;										// タイマー初期化
	SetTag(BulletObjectParam::tag);					// タグの初期化
	active = BulletObjectParam::active;				// 弾が存在するか否か
	livetime = BulletObjectParam::livetime;			// 弾が画面にでている時間
	spead = BulletObjectParam::spead;				// 弾のスピード
	startTrigger = BulletObjectParam::startTrigger;	// 開始時に一度だけ再生される
	p_map = New_p_map;								// マップ情報の渡し

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
	direction = NewDirection;

	// 位置の設定
	{
		p_transform->scale = BulletObjectParam::scale;			// 大きさの初期化
		p_transform->position = BulletObjectParam::position;	// 座標の初期化
	}

	// 画像の設定
	{
		//レンダラーの設定
		std::shared_ptr<Texture> tex = GetComponent<SpriteRenderer>()->LoadTexture(BulletObjectParam::BulletObjTexName);

		//アニメーターの設定
		SpriteAnimator* p_spriteAnimator = AddComponent<SpriteAnimator>(hft::HFFLOAT2(1, 1));
		hft::HFFLOAT2 div = p_spriteAnimator->GetDivision();

		//animationの設定
		// 通常
		SpriteAnimation anim1(div, { 0,0 }, 1);
		anim1.InActive();
		anim1.SetID(0);
		anim1.SetType(SPRITE_ANIM_TYPE::NORMAL);
		anim1.SetPriority(0);
		float flame = 1;

		for (int i = 0; i < 1; i++)
		{
			anim1.GetCellRef(i).flame = flame;
		}
		p_spriteAnimator->AddAnimation(anim1);
		p_spriteAnimator->Play(0);
		p_spriteAnimator->SetIsActive(false);
	}

	// 本体のコライダー設定
	auto bodyCollider = AddComponent<BoxCollider2D>();
	bodyCollider->Init();
	hft::HFFLOAT3 p_size = p_transform->scale;					// サイズ分当たり判定をとる
	bodyCollider->SetSize(p_size);
	bodyCollider->SetIsActive(false);
}

//===============================================================================================
// 弾オブジェクトの更新処理
//===============================================================================================
void BulletObject::Update()
{
	// 弾が存在しないとき、処理を終了する
	if (GetBulletActive() == false)return;

	// 処理がシンプルなので状態で分けずにここに書いてます
	//-----------------------------------------------------------------------------------
	timer++;												// フレーム更新
	// 一回実行する処理
	if (startTrigger == true)
	{
		startTrigger = false;
		AddPos();
		GetComponent<BoxCollider2D>()->SetIsActive(true);	// 当たり判定をアクティブ
		GetComponent<SpriteRenderer>()->SetIsActive(true);	// 描写をする
		GetComponent<SpriteAnimator>()->Play(0);			// 再生するアニメーションIDは0
	}
	
	UpdatePos();											// 座標の更新
	CheakMyPos();											// 端に到達してないか確認

	// 存在できる時間を超過した場合の処理
	if (timer >= livetime)
	{
		timer = 0;											// タイマーを元に戻す
		GetComponent<SpriteAnimator>()->Stop(0);			// 停止するアニメーションIDは0
		GetComponent<SpriteRenderer>()->SetIsActive(false);	// 描写をしない
		GetComponent<BoxCollider2D>()->SetIsActive(false);	// 当たり判定を非アクティブ
		startTrigger = true;								// 次回発射される時に実行されるようにする
		SetBulletActive(false);								// 自らの行動を非アクティブ
	}
}

//===============================================================================================
// 出現させる位置を調節する
//===============================================================================================
void BulletObject::AddPos()
{
	switch(direction){
	case RIGHT: p_transform->position.x += 100.f; break;
	case UP:	p_transform->position.y += 100.f; break;
	case LEFT: p_transform->position.x -= 100.f; break;
	case DOWN:	p_transform->position.y -= 100.f; break;
	default:
		std::cout << "座標調節エラー\n";
	}
}

//===============================================================================================
// 方向別に座標を更新させる (右向きなら右方向へ座標を更新、上向きなら上方向へ座標を更新..)
//===============================================================================================
void BulletObject::UpdatePos()
{
	// 今の弾オブジェクトの座標取得
	const hft::HFFLOAT3 NowPos = p_transform->position;

	switch (direction){
	case RIGHT:	p_transform->position.x = NowPos.x + spead * 1.0f; break;
	case UP:	p_transform->position.y = NowPos.y + spead * 1.0f; break;
	case LEFT:	p_transform->position.x = NowPos.x - spead * 1.0f; break;
	case DOWN:	p_transform->position.y = NowPos.y - spead * 1.0f; break;
	default:
		std::cout << "弾オブジェクト座標更新エラー\n";
	}
}

//================================================================================================
// 方向別にマップの枠組みから出ないようにする(上方向ならTopと比較、右方向ならRightと比較..)
//================================================================================================
void BulletObject::CheakMyPos()
{
	// マップの端から超えるようなら反対側の座標を代入する
	switch (direction)
	{
	case RIGHT:	if (RightBottom.x < (p_transform->position.x)) { this->p_transform->position.x = LeftTop.x;}break;
	case UP:	if (LeftTop.y < (p_transform->position.y)) { this->p_transform->position.y = RightBottom.y;}break;
	case LEFT:	if (LeftTop.x > (p_transform->position.x)) { this->p_transform->position.x = RightBottom.x;}break;
	case DOWN:	if (RightBottom.y > (p_transform->position.y)) { this->p_transform->position.y = LeftTop.y;}break;
	default:
		std::cout << "座標チェックエラー\n";
	}
}

//================================================================================================
// OnCollisionEnterの処理
//================================================================================================
void BulletObject::OnCollisionEnter(Collider* _p_col)
{
	// 相手の情報を取得
	GameObject* col = _p_col->GetGameObject();
	std::string other_tag = col->GetTag();
	TrackObject* player = dynamic_cast<PlayerObject*>(col);
	TrackObject* bite = dynamic_cast<BiteEnemy*>(col);
	TrackObject* gun = dynamic_cast<GunEnemy*>(col);
	TrackObject* bomb = dynamic_cast<BombEnemy*>(col);
	TrackObject* thorn = dynamic_cast<ThormObject*>(col);
	TrackObject* connect = dynamic_cast<ConnectObject*>(col);
	// ヒットしたのがこれら以外の場合、処理を終了する
	bool Hit = (player||bite || gun || bomb || thorn  || connect);
	if (Hit == false)return;
	if (other_tag == "DamageObject" || other_tag == "Gun" || other_tag == "Bite"||other_tag=="Player"||other_tag=="Enemy")
	{
		timer = 0;											// タイマーを元に戻す
		GetComponent<SpriteAnimator>()->Stop(0);			// 停止するアニメーションIDは0
		GetComponent<SpriteRenderer>()->SetIsActive(false);	// 描写をしない
		GetComponent<BoxCollider2D>()->SetIsActive(false);	// 当たり判定を非アクティブ
		startTrigger = true;								// 次回発射される時に実行されるようにする
		SetBulletActive(false);								// 自らの行動を非アクティブ
	}
}