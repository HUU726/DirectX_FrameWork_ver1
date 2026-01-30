#pragma once
#include "../00-TrackObject/TrackObject.h"
#include "../../../../99-Lib/01-MyLib/07-Component/03-Collider/00-Collider/Collider.h"


//朝日奈担当連結オブジェクトクラス
//スプライトレンダラー側にオフセットが無いので、連結部分の描画はオブジェクトを複数配置変更して管理する
//検査用コライダーに接触したコライダーが連結ブロックかどうかを検索するのはキャスト形式で行う

class BoxCollider2D;
class BaseMap;

class ConnectObject : public TrackObject
{
private:
	//本体部分のパラメータ
	static int instanceCounter;		//現在何個生成されているかを全体で共有
	int myInstanceNumber;			//自身の番号

	BoxCollider2D* bodyCollider;


	//検査用コライダーのパラメータ
	int searchCollCell;				//コライダーの長さ(マス数)
	float searchCollThickness;		//コライダーの厚み
	BoxCollider2D* searchCollVert;	//縦のコライダー
	BoxCollider2D* searchCollHori;  //横のコライダー
	
	//接触した連結オブジェクト配列
	std::vector<ConnectObject*> connectObjArray;

	//攻撃判定用のオブジェクト配列
	std::vector<GameObject2D*> emitAttackObjects;

	//拡大率調整用のスケールレート
	float scallingLate;

public:
	ConnectObject();
	~ConnectObject();
	void Init(BaseMap* map);
	void Update() override;

	//全ての攻撃判定オブジェクトのアクティブ状態をリセット
	void ResetAttackObjectsActive();

	//他の連結ブロックとの接続状態を検査する
	void SearchConnectedState();

	//連結部分に攻撃判定用のオブジェクトを配置する
	void EmitAttackAtConnection(const hft::HFFLOAT3 tarPos);

	//上下左右、どちらの方向に繋がっているかを確認する
	hft::HFFLOAT3 GetConnectionAxis(hft::HFFLOAT3 originPos, hft::HFFLOAT3 tarPos);

	//接触相手の座標から自身の座標まで、何マス分あるか検知。マスのサイズは外部から指定する
	int GetContactTileDistance(hft::HFFLOAT3 originPos, hft::HFFLOAT3 tarPos, float cellSize);

	////接触相手の座標から自身の座標までの距離を測定。XYどちらかの軸
	float GetContactDistance(hft::HFFLOAT3 originPos, hft::HFFLOAT3 tarPos);

	//自身の座標から接触相手の座標まで、縦横いずれかの向きで攻撃判定用オブジェクトを配置する
	void SpawnAttackObjects(hft::HFFLOAT3 tarPos, hft::HFFLOAT3 connectDir);

	//自身の生成番号を取得
	const int GetInstanceNumber() { return myInstanceNumber; }

	//本体部分のコライダーを取得
	const BoxCollider2D* GetBodyCollider()
	{
		if (bodyCollider)
		{
			return bodyCollider;
		}
		else
		{
			return nullptr;
		}
	}	

	/**
	* @brief	コライダー同士が衝突した際の処理
	* @param	Collider2D*	_p_col	2D用コライダーのポインタ
	*/
	void OnCollisionEnter(Collider* _p_col) override;

	/**
	* @brief	コライダー同士が離れた際の処理
	* @param	Collider2D*	_p_col	2D用コライダーのポインタ
	*/
	void OnCollisionExit(Collider* _p_col) override;
	
	/**
	* @brief	コライダー同士が接触中の処理
	* @param	Collider2D*	_p_col	2D用コライダーのポインタ
	*/
	void OnCollisionStay(Collider* _p_col) override;
};