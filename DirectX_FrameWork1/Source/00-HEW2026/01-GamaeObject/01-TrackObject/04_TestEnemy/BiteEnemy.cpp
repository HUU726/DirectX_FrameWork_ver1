#include "DirectX_FrameWork1/Source/99-Lib/01-MyLib/07-Component/03-Collider/01-Collider2D/BoxCollider2D.h"
#include "../../../../99-Lib/01-MyLib/07-Component/06-Animator/01-SpriteAnimator/SpriteAnimator.h"
#include "../../../../99-Lib/01-MyLib/07-Component/02-Renderer/01-SpriteRenderer/SpriteRenderer.h"

#include"BiteEnemy.h"
#include"BiteEnemyParam.h"

#define RIGHT 0:
#define LEFT 2:

class BoxCollider2D;

// このエネミーのタグ:"Enemy"

BiteEnemy::BiteEnemy()
{
	
}

BiteEnemy::~BiteEnemy()
{

}

// 初期化=============================================================
void BiteEnemy::Init(const int& direction)
{
	timer = 0;	// タイマーの初期化
	tag = BiteEnemyParam::tag;	// タグ:Bite
	hitstoptime = BiteEnemyParam::hitstoptime;	// ヒットストップ時間
	//currentState = BiteEnemy::defoult1;
	defoulttime_1 = BiteEnemyParam::defoult1;
	defoulttime_2 = BiteEnemyParam::defoult2;
	attacktime = BiteEnemyParam::attack;
	spinttime = BiteEnemyParam::spin;
	deadtime = BiteEnemyParam::dead;
	if (direction < 4 && direction > 0)SetDirection(direction);
	else SetDirection(0);
	for (int i = 0; i < 4; i++)
	{
		offset[i] = BiteEnemyParam::offset[i];
	}

	// 位置の設定
	{
		p_transform->scale = BiteEnemyParam::scale;
		p_transform->position = BiteEnemyParam::position;
	}

	// レンダラーの設定
	std::shared_ptr<Texture> tex = GetComponent<SpriteRenderer>()->LoadTexture(BiteEnemyParam::BiteEnemyTexName);
	// アニメーターの設定
	SpriteAnimator* p_spriteAnimator = AddComponent<SpriteAnimator>(hft::HFFLOAT2(7, 8));
	hft::HFFLOAT2 div = p_spriteAnimator->GetDivision();

	// アニメーション登録用のヘルパー
	auto AddAnimationSafe = [&](int id, hft::HFFLOAT2 start, int flameCount, SPRITE_ANIM_TYPE type, int priority = 0)
		{
			SpriteAnimation anim(div, start, flameCount);
			anim.Active();
			anim.SetID(id);
			anim.SetType(type);
			anim.SetPriority(priority);
			for (int i = 0; i < flameCount; i++)
			{
				anim.GetCellRef(i).flame = flameCount;
			}
			p_spriteAnimator->AddAnimation(anim);
		};

	// 各方向ごとに登録
	// 通常
	AddAnimationSafe(0, { 0,0 }, 10, SPRITE_ANIM_TYPE::LOOP);   // 横向き
	AddAnimationSafe(1, { 2,4 }, 10, SPRITE_ANIM_TYPE::LOOP);   // 上向き 														
	AddAnimationSafe(2, { 4,3 }, 10, SPRITE_ANIM_TYPE::LOOP);	// 下向き										
	// 攻撃
	AddAnimationSafe(3, { 2,4 }, 9, SPRITE_ANIM_TYPE::NORMAL);  // 横向き
	AddAnimationSafe(4, { 1,6 }, 6, SPRITE_ANIM_TYPE::NORMAL);  // 上向き 														
	AddAnimationSafe(5, { 3,5 }, 6, SPRITE_ANIM_TYPE::NORMAL);	 // 下向き

	// 回転
	AddAnimationSafe(6, { 1,1 }, 1, SPRITE_ANIM_TYPE::NORMAL);    // 右向き
	AddAnimationSafe(7, { 5,3 }, 2, SPRITE_ANIM_TYPE::NORMAL);    // 上向き 														
	AddAnimationSafe(8, { 2,5 }, 2, SPRITE_ANIM_TYPE::NORMAL);	  // 左向き
	AddAnimationSafe(9, { 5,3 }, 1, SPRITE_ANIM_TYPE::NORMAL);    // 下向き 														

	// 死亡
	AddAnimationSafe(10, { 5,3 }, 2, SPRITE_ANIM_TYPE::NORMAL);    // 全方向共通

	p_spriteAnimator->SetIsActive(false);

	// 本体のコライダーの設定
	bodyCollider = AddComponent<BoxCollider2D>();
	//bodyCollider->SetIsActive(true);
	
	// 攻撃マスの位置を自身のサイズ分,ずらす
	const hft::HFFLOAT3 size = bodyCollider->GetSize();
	offset[0] = { size.x,0.0f,0.0f };
	offset[1] = { 0.0f,size.y,0.0f };
	offset[2] = { -(size.x),0.0f,0.0f };
	offset[3] = { 0.0f,-(size.y),0.0f };

	//攻撃マスの設定
	attackCollider = AddComponent<BoxCollider2D>();
	attackCollider->SetSize(bodyCollider->GetSize());	// 本体と同じサイズ
	attackCollider->SetOffset({ size.x,0.0f,0.0f });		// 初期は右に出現させる
	attackCollider->SetIsActive(false);

	std::cout << "BiteEnemyパラメータ完了\n";
}

// 更新===============================================================
void BiteEnemy::Update()
{
	timer = 0;
	/*
	switch (currentState)
	{
	case defoult1:
		Defoult1();
		break;
	case defoult2:
		Defoult2();
		break;
	case attack:
		Attack();
		break;
	case spin:
		Spin();
		break;
	case dead:
		Dead();
		break;
	default:
		std::cout << "状態エラー\n";
	}
	*/
}

/*
//==================================================================================
// 通常状態の行動
//==================================================================================
void BiteEnemy::Defoult1()
{
	std::cout << "通常状態1実行中\n";
	std::cout << "現在の方向:" << GetDirection() << "\n";
	// アニメーション変更
	switch(GetDirection()){
	case 0: GetComponent<SpriteAnimator>()->Play(0); break;
	case 1: GetComponent<SpriteAnimator>()->Play(1); break;
	case 2: GetComponent<SpriteAnimator>()->Play(0); break;
	case 3: GetComponent<SpriteAnimator>()->Play(2); break;


	if (timer > defoulttime_1)
	{
		currentState = BiteEnemy::attack;		// 攻撃へ
		timer = 0;
	}
}

void BiteEnemy::Defoult2()
{
	std::cout << "通常状態2実行中\n";
	GetComponent<SpriteAnimator>()->Stop((GetDirection() * 3) + 1);
	GetComponent<SpriteAnimator>()->Play(GetDirection() * 3);
	if (timer > defoulttime_2)
	{
		currentState = BiteEnemy::spin;			// 回転へ
		timer = 0;
	}
}

//==================================================================================
// 攻撃状態の行動
//==================================================================================
void BiteEnemy::Attack()
{
	std::cout << "攻撃状態実行中\n";
	int dir = 0;
	if (dir < 0 || dir >= 4)dir = 0;
	attackCollider->SetOffset(offset[dir]);
	attackCollider->SetOffset(offset[GetDirection()]);
	GetComponent<SpriteAnimator>()->Stop(GetDirection() * 3);
	GetComponent<SpriteAnimator>()->Play((GetDirection() * 3) + 1);
	attackCollider->SetIsActive(true);			// 当たり判定をアクティブに
	if (timer > attacktime)
	{
		currentState = BiteEnemy::defoult2;		// 通常状態へ
		attackCollider->SetIsActive(false);			// 当たり判定を非アクティブに
		timer = 0;
	}
}

//==================================================================================
// 回転状態の行動
//==================================================================================
void BiteEnemy::Spin()
{
	std::cout << "回転状態実行中\n";
	GetComponent<SpriteAnimator>()->Stop(GetDirection() * 3);
	GetComponent<SpriteAnimator>()->Play((GetDirection() * 3) + 2);
	if (timer > spinttime)
	{
		GetComponent<SpriteAnimator>()->Stop((GetDirection() * 3) + 2);
		currentState = BiteEnemy::defoult1;		// 通常状態へ
		SetDirection(GetDirection() + 1);		// 方向変換
		if (GetDirection() >= 4) { SetDirection(0); }
		timer = 0;
	}
}


//==================================================================================
// 死亡状態の行動
//==================================================================================
void BiteEnemy::Dead()
{
	CEnemy::DownEnemyCount();
	// 当たり判定停止
	bodyCollider->SetIsActive(false);
	attackCollider->SetIsActive(false);
	// アニメーション
	GetComponent<SpriteAnimator>()->Stop(GetDirection() * 3);
	GetComponent<SpriteAnimator>()->Stop((GetDirection() * 3) + 1);
	GetComponent<SpriteAnimator>()->Stop((GetDirection() * 3) + 2);
	GetComponent<SpriteAnimator>()->Play(12);
	if (timer > dead)
	{
		std::cout << "BiteEnemy機能停止\n";
		SetIsActive(false);
	}
}


//@brief	コライダー同士が衝突した際の処理
// @param	Collider2D* _p_col	2D用コライダーのポインタ
*/
void BiteEnemy::OnCollisionEnter(Collider* _p_col)
{
	// 接触相手の情報を取得
	GameObject* col = _p_col->GetGameObject();

	if (_p_col == bodyCollider)
	{
		// 本体がヒット
		if (col->GetTag() == "Object")
		{
			timer = 0;
			std::cout << "BIteEnemy本体にヒット\n";
			//currentState = BiteEnemy::dead;
		}
	}
	else if (_p_col == attackCollider)
	{
		// 攻撃がヒット
		std::cout << "BiteEnemyの攻撃がヒット\n";
		return;
	}
}