#pragma once


enum COMP_MNG_TYPES
{
	COMP_INPUT = 0,
	COMP_COLLIDER2D,
	COMP_COLLIDER3D,
	COMP_ANIMATOR,
	COMP_CAMERA2D,
	COMP_CAMERA3D,
	COMP_LIGHT,
	COMP_RENDERER2D,
	COMP_RENDERER3D,
	COMP_MAX,
	COMP_BEFORE_RENDER = COMP_RENDERER2D,
};


class IF_ComponentManager
{
private:
	COMP_MNG_TYPES type;

public:

	COMP_MNG_TYPES GetType() { return type; }
	virtual void Action() = 0;
};