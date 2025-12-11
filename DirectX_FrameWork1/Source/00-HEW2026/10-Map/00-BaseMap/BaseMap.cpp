#include "BaseMap.h"

#include "../../01-GamaeObject/01-TrackObject/00-TrackObject/TrackObject.h"

void BaseMap::Slide()
{
	for (auto& data : slideDatas)
	{
		SearchOnLineObjects(data);
		SlideTrackObject(data);
		data.power *= 0.8;
		if (data.power < 1)
			data.power = 0;
	}

	for (auto& data : slideDatas)
	{
		if (data.power == 0)
		{
			auto it = std::find(slideDatas.begin(), slideDatas.end(), data);
			if (it != slideDatas.end())
				slideDatas.erase(it);
		}
	}
}

void BaseMap::SearchOnLineObjects(SlideData& _data)
{
	_data.trackObjects.clear();

	for (const auto& obj : onMapTrackObjects)
	{
		if (_data.moveVec.x)
		{
			if (obj->GetLineIndex().x == _data.moveVec.x)
				_data.trackObjects.push_back(obj);
		}
		else if (_data.moveVec.y)
		{
			if (obj->GetLineIndex().y == _data.moveVec.y)
				_data.trackObjects.push_back(obj);
		}
	}

}

void BaseMap::SlideTrackObject(SlideData& _data)
{

	for (auto obj : _data.trackObjects)
	{
		Transform* p_trf = obj->GetTransformPtr();
		p_trf->position += _data.moveVec * _data.power;
	}
}


void BaseMap::SetSlideData(const hft::HFFLOAT2& _anchorPos, const hft::HFFLOAT2& _moveVec, const float& _power)
{
	SlideData data{ _anchorPos,_moveVec,_power };
	slideDatas.push_back(data);
}

void BaseMap::Init(const int& _width, const int& _height)
{

}