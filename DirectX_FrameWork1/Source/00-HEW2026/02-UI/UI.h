#pragma once
#include "../../99-Lib/01-MyLib/06-GameObject/01-2DGameObject/GameObject2D.h"

#include"../../04-Input/Input.h"


//UIの種類
enum Type_UI
{
	NormalType,	 //初期値から何も作用しない。背景など
	ButtonType,  //押下を検知等
};

class UI : public GameObject2D
{
private:
	hft::HFFLOAT2 initialScale;		//初期の拡大率(アニメーション後の引き戻しで使う)
	Type_UI type;					//UIの種類
	bool isPressed = false;			//押されているかどうか
	bool isTrigger = false;
	bool isMouseInside = false;		//マウスが自身の範囲内に存在するか

	Button::KeyBord targetKey;
	Button::XBox targetXboxBotton;

	bool coverTrg = false;
	bool preISMouseInside = false;
	int onSE;
	int dicSE;

public:
	UI();

	//初期位置、サイズ、テクスチャ名、UIの種類を設定
	void Init(const hft::HFFLOAT3 pos, const hft::HFFLOAT2 scale, const char* tex, Type_UI type);

	void Update() override;

	//自身に対応するキー、XBoxボタンを設定。そのキーが押されたかどうかを他の関数で検知
	void SetTargetKey(Button::KeyBord key);
	void SetTargetXBoxButton(Button::XBox botton);

	//ボタンの押下状態を更新
	void UpdateIsPressed();

	//ボタンの桜花のトリガーを更新
	void UpdateIsTrigger();

	//mouseが自身の範囲内にあるかの状態を更新
	void UpdateIsMouseInside();

	//押されているかどうか
	bool GetIsPressed();
	bool GetIsTrigger();
	bool GetIsMouseInside();

	void AnimationPressed();
	void AnimationMouseInside();
};