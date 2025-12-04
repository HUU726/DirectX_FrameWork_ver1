#pragma once

#include "../../GameObject.h"

class Camera3D;

class CameraObject3D : public GameObject
{
private:
	Camera3D* p_comp_camera;		//3Dカメラコンポネントポインタ
	Transform* p_standTransform;	//追跡するTransform

public:
	CameraObject3D();
	~CameraObject3D();
	hft::HFFLOAT3 GetForward() const;
	hft::HFFLOAT3 GetRight() const;
	hft::HFFLOAT3 GetUp() const;

	/**
	* @brief	カメラの位置座標を設定
	* @param	hft::HFFLOAT3	_pos	カメラの座標
	*/
	void SetStandPos(hft::HFFLOAT3 _pos);
	/**
	* @brief	カメラの位置座標をポインタで指定
	* @param	Transform*	_p_transform	カメラの座標をポインタで変更
	*/
	void SetStandPos(Transform* _p_transform);
	/**
	* @brief	カメラが見る先を設定
	* @param	GameObject*		_p_gameObject	見るオブジェクト
	*/
	void SetTarget(GameObject* _p_gameObject);

	void Init() override;
	void Update() override;
};

