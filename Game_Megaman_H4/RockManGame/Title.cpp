#include "Title.h"


Title::Title(void)
{
}


Title::~Title(void)
{
}

Title::Title(int id,Sprite *sprite,int x,int y,int width,int height)
{
	this->id = id;
	this->sprite = sprite;
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
}

Title::Title(int id,Sprite *sprite,int x,int y)
{
	this->id = id;
	this->sprite = sprite;
	this->x = x;
	this->y = y;
	this->width = 40;
	this->height = 40;
}

void Title::Render(LPD3DXSPRITE spritehandle, CCamera * cam)
{
	D3DXVECTOR3 pos = cam->GetPointTransform(this->x,this->y);
	this->sprite->RenderTile(spritehandle,pos);
	

}