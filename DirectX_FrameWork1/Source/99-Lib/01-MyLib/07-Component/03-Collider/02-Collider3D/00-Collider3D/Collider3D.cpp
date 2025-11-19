#include "Collider3D.h"



void Collider3D::SetFuncCollisionEnter(CallbackOnCollisionEnter3D _func)
{
	funcOnCollisionEnter = _func;
}


void Collider3D::OnCollisionEnter3D(Collider3D* _p_col)
{
	if (funcOnCollisionEnter != nullptr)
		funcOnCollisionEnter(_p_col);
}
