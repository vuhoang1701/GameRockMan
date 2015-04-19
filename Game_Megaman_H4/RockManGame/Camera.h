#pragma once
#include "d3dx9.h"


enum Direction			// huong di chuyen cua object
{
	left,
	right,
	up,
	down,
};

class CCamera
{
private:
	bool canMoveLeft, // cam co the di chuyen sang trai
		canMoveRight, // cam co the di chuyen sang phai
		canMoveUp, // cam co the di chuyen len
		canMoveDown; // // cam co the di chuyen xuong

	D3DXMATRIX _MatrixTransform;
public:
	
	D3DXVECTOR2 _pos;
	int _width;
	int _height;
	CCamera();
	~CCamera(void);
	void Update(int , int , int); 
	D3DXVECTOR3 GetPointTransform(int x, int y);
	void Check(int a[73][272], Direction);
};
