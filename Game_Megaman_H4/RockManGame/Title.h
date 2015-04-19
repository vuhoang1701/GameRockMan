#pragma once
#include "Sprite.h"
#include "Camera.h"
class Title
{
protected:
	
	
	int width;
	int height;

public:
	int id;
	int x;
	int y;
	Sprite *sprite;
	Title(int ,Sprite *,int ,int ,int ,int);
	Title(int ,Sprite *,int ,int );
	void Render(LPD3DXSPRITE,CCamera *);
	Title(void);
	~Title(void);
};

