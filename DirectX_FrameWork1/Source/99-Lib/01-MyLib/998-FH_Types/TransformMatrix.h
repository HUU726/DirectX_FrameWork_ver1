#pragma once

#include "./HF_FLOAT.h"

#define PAI (3.141592f)


namespace hft
{

	struct TransformMatrix
	{
		DirectX::XMMATRIX matPosition;	//移動行列
		DirectX::XMMATRIX matRotation;	//回転行列
		DirectX::XMMATRIX matScale;		//スケーリング行列

		TransformMatrix() : 
			matPosition(DirectX::XMMatrixIdentity()),
			matRotation(DirectX::XMMatrixIdentity()),
			matScale(DirectX::XMMatrixIdentity())
		{}

		/**
		* @brief	hft::HFFLOAT4からDirectX::XMMATRIXに変換
		* @param	hft::HFFLOAT4	_pos	座標
		* @return	DirectX::XMMATRIX	行列に変換した座標
		*/
		DirectX::XMMATRIX ConversionPosition(hft::HFFLOAT4 _pos);
		/**
		* @brief	hft::HFFLOAT4からDirectX::XMMATRIXに変換
		* @param	hft::HFFLOAT4	_rot	回転
		* @return	DirectX::XMMATRIX	行列に変換した回転
		*/
		DirectX::XMMATRIX ConversionRotation(hft::HFFLOAT3 _rot);
		/**
		* @brief	hft::HFFLOAT4からDirectX::XMMATRIXに変換
		* @param	hft::HFFLOAT4	_scale	スケール
		* @return	DirectX::XMMATRIX	行列に変換したスケール
		*/
		DirectX::XMMATRIX ConversionScale(hft::HFFLOAT3 _scale);

		/**
		* @brief	ワールド変換行列を返す
		*/
		DirectX::XMMATRIX GetMatrixWorld();
	};

}