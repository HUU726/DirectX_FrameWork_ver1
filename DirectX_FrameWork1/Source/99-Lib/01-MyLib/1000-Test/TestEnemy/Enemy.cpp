#include"Enemy.h"


void CEnemy::SetState(const int& NewState)
{
	e_state = NewState;
}

int CEnemy::GetState()
{
	return e_state;
}

void CEnemy::SetFlame(const float& NewFlame)
{
	e_flame = NewFlame;
}

float CEnemy::GetFlame()
{
	return e_flame;
}