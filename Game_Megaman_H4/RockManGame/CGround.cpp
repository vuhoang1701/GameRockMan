#include "CGround.h"


CGround::CGround()
{

}

CGround::CGround(LPDIRECT3DDEVICE9 d3ddev, int id, int x, int y)
{
	switch (id)
	{
	case 0:
		_Spr = new Sprite(d3ddev,"..\\Data\\Bar\\Left-Bar.png", 16, 16, 1, 1, 1); break;
	case 1:
		_Spr = new Sprite(d3ddev,"..\\Data\\Bar\\Mid-Bar.png", 16, 16, 1, 1, 1); break;
	case 2:
		_Spr = new Sprite(d3ddev,"..\\Data\\Bar\\Right-Bar.png", 16, 16, 1, 1, 1);break;
	default:
		break;
	}
	_Id = id;
	_Pos.x = x;
	_Pos.y = y;
	_Vx = 0;
	_Vy = 0;
	_Bound.top		= _Pos.y + (_Spr->_Height/2);
	_Bound.bottom	= _Pos.y - (_Spr->_Height/2);
	_Bound.left		= _Pos.x - (_Spr->_Width/2);
	_Bound.right	= _Pos.x + (_Spr->_Width/2);
}

CGround::~CGround()
{
	
}