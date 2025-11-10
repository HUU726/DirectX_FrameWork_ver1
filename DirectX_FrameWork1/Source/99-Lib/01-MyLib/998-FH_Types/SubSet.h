#pragma once

#include <string>

namespace hft
{
	struct SubSet
	{
		std::string materialName;	//マテリアル名
		unsigned int indexNum;		//インデックス数
		unsigned int vertexNum;		//頂点数
		unsigned int indexBase;		//開始インデックス
		unsigned int vertexBase;	//開始頂点
		unsigned int materialID;	//マテリアル番号
	};
}