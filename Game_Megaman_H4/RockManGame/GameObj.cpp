#include "GameObj.h"


CGameObj::CGameObj(void)
{
	_isDead = false;
}
CGameObj::CGameObj(int id, int x, int y, Sprite *spr)
{
	_isDead = false;
	_isAlive = true;
	_Id = id;
	_Spr= spr;
	_Pos.x = x;
	_Pos.y = y;
	_Bound.top		= _Pos.y + (_Spr->_Height/2);
	_Bound.bottom	= _Pos.y - (_Spr->_Height/2);
	_Bound.left		= _Pos.x - (_Spr->_Width/2);
	_Bound.right	= _Pos.x + (_Spr->_Width/2);
	_Vx = 0;
	_Vy = 0;
}

RECT* CGameObj::GetBound()
{
	RECT* rect = new RECT();
	rect->top = _Bound.top;
	rect->left = _Bound.left;
	rect->bottom = _Bound.bottom;
	rect->right = _Bound.right;
	return rect;
}



void CGameObj::Render(LPD3DXSPRITE spritehandle, CCamera *Cam)
{
	D3DXVECTOR3 pos =	Cam->GetPointTransform(_Pos.x,_Pos.y);
	_Spr->Render(spritehandle,pos);
}



CGameObj::~CGameObj(void)
{
}
