#pragma once
#include "../00-TrackObject/TrackObject.h"

//朝日奈担当連結オブジェクトクラス
//スプライトレンダラー側にオフセットが無いので、連結部分の描画はオブジェクトを複数配置変更して管理する
//検査用コライダーに接触したコライダーが連結ブロックかどうかを検索するのはキャスト形式で行う

class BoxCollider2D;


class ConnectObject : public TrackObject
{
private:
	//本体部分のパラメータ
	static int instanceCounter;		//現在何個生成されているかを全体で共有
	int myInstanceNumber;			//自身の番号

	//検査用コライダーのパラメータ
	int searchCollCell;				//コライダーの長さ(マス数)
	float searchCollThickness;		//コライダーの厚み
	BoxCollider2D* searchCollVert;	//縦のコライダー
	BoxCollider2D* searchCollHori;  //横のコライダー

	//攻撃判定用のオブジェクト
	std::vector<GameObject2D*> emitAttackObj;
public:
	ConnectObject();
	void Init() override;
	void Update() override;

	//他の連結ブロックとの接続状態を検査する
	bool SearchConnectedState();

	//連結部分に攻撃判定用のオブジェクトを配置する
	void EmitAttackAtConnection(const std::vector<Transform*> targetTrfArray);

	//ゲッター
	const int GetInstanceNumber() { return myInstanceNumber; }
};

