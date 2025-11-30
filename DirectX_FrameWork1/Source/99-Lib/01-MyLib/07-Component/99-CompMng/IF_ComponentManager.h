#pragma once


enum COMP_MNG_TYPES
{
	COMP_INPUT = 0,
	COMP_COLLIDER3D,
	COMP_COLLIDER2D,
	COMP_ANIMATOR,
	COMP_CAMERA3D,
	COMP_CAMERA2D,
	COMP_LIGHT,
	COMP_RENDERER3D,
	COMP_RENDERER2D,
	COMP_MAX,
	COMP_BEFORE_RENDER = COMP_RENDERER3D,
};


class IF_ComponentManager
{
protected:
	COMP_MNG_TYPES type;

public:

	void SetType(COMP_MNG_TYPES _type) { type = _type; }
	COMP_MNG_TYPES GetType() { return type; }
	virtual void Action() = 0;
};