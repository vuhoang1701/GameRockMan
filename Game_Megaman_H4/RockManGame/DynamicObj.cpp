#include "DynamicObj.h"

DynamicObj::DynamicObj(int id,float x,float y, Sprite* Sprite,float Vel_x,float Vel_y):CGameObj(id,x,y,Sprite)
{
	_Dir = right;
	this->m_velocX = Vel_x;
	this->m_velocY = Vel_y;
}

DynamicObj::DynamicObj(void)
{
}
void DynamicObj::SetVeloc(float x, float y)
{

}
D3DXVECTOR2 DynamicObj::GetVeloc()
{
	return D3DXVECTOR2(0,0);
}
void DynamicObj::Update(CCamera* Cam, int time)
{
}

DynamicObj::~DynamicObj(void)
{
}
