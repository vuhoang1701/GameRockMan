#include "Camera.h"


CCamera::CCamera()
{
	canMoveRight = true;
	canMoveLeft = false;
	canMoveDown = false;
	canMoveUp = false;
	_pos.x = 0;
	_pos.y = 224;
	_width = 256;
	_height = 224;
	D3DXMatrixIdentity(&_MatrixTransform);
	_MatrixTransform._22 = -1;
}
	
CCamera::~CCamera(void)
{
}


void CCamera::Update(int x, int y, int time)
{	
	//if(canMoveRight == true || canMoveLeft == true)
		_pos.x = x - _width/2;
	if(_pos.x <= 0)
	{
		_pos.x = 0;
	}

}
void CCamera::Check(int t[73][272], Direction direction)
{
	int _rowtop = 73 - _pos.y/16 + 1;
	int _rowbot = 73 - (_pos.y - _height)/16 + 1;
	int _colleft = _pos.x/16;
	int _colright = (_pos.x + _width)/16;



	switch (direction)
	{
	case left:
		if(t[_rowbot][_colleft-1] !=1 )
		{
			canMoveLeft = true;
			canMoveRight = false;
			canMoveDown = false;
			canMoveUp = false;
		}
		else
		{
			canMoveLeft = false;
			canMoveRight = true;
		}
		break;
	case right:
		if(t[_rowbot][_colright + 1] !=1 )
			{
				canMoveRight = true;
				canMoveLeft = false;
				canMoveDown = false;
				canMoveUp = false;
			}
		else
		{
			canMoveRight = false;
		}
		break;
	case up:
		break;
	case down:
		break;
	default:
		break;
	}



}

D3DXVECTOR3 CCamera::GetPointTransform(int x, int y)
{
	_MatrixTransform._41 = - _pos.x;
	_MatrixTransform._42 = _pos.y;

	D3DXVECTOR3 pos(x, y, 0);
	D3DXVECTOR4 v_result;

	D3DXVec3Transform(&v_result, &pos, &_MatrixTransform);

	return D3DXVECTOR3(v_result.x, v_result.y,0);
}
