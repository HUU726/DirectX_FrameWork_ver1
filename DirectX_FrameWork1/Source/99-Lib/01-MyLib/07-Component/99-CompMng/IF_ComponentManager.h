#pragma once


enum COMP_MNG_TYPES
{
	COLLIDER2D = 0,
	COLLIDER3D,
	ANIMATOR,
	CAMERA2D,
	CAMERA3D,
	LIGHT,
	RENDERER2D,
	RENDERER3D,
	MAX_COMP,
};


class Base_ComponentManager
{
private:
	COMP_MNG_TYPES type;

public:

	COMP_MNG_TYPES GetType() { return type; }
};