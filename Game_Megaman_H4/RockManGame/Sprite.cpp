#include "Sprite.h"


Sprite::Sprite(LPDIRECT3DDEVICE9 d3ddev,char* Path,int Width,int Height,int Count,int Spriteperrow)
{
	_Index = 0;
	_Image = new Texture(d3ddev);
	_Image->LoadTexture(Path,D3DCOLOR_XRGB(0,0,255));
	_Width = Width;
	_Height = Height;
	_Count = Count;
	_SpritePerRow = Spriteperrow;
	_Index = 0;
	
}

Sprite::Sprite(LPDIRECT3DDEVICE9 d3ddev,char* Path,int Width,int Height,int Count,int Spriteperrow, int Spritepercol)
{

	_Image = new Texture(d3ddev);
	_Image->LoadTexture(Path,D3DCOLOR_XRGB(0,0,255));
	_Width = Width;
	_Height = Height;
	_Count = Count;
	_SpritePerRow = Spriteperrow;
	_SpritePerCol = Spritepercol;
	_Index = 0;
	
}

void Sprite::Render(LPD3DXSPRITE spritehandle, D3DXVECTOR3 pos)
{
	D3DXVECTOR3 center((float)_Width/2,(float)_Height/2,0);
	RECT srect;
	
	if(_Index < _SpritePerRow )
	{
		srect.left = (_Index % _SpritePerRow)*(_Width);
		srect.top = 0;
	}else
	{
		srect.left = ((_Index - _SpritePerRow) % _SpritePerRow)*(_Width);
		srect.top = _Height;
	}
	srect.right = srect.left + _Width;
	srect.bottom = srect.top + _Height;
	spritehandle->Draw(
		_Image->GetTexture(),
		&srect,
		&center,
		&pos,
		D3DCOLOR_XRGB(255,255,255)
		);
}


void Sprite::RenderTile(LPD3DXSPRITE spritehandle, D3DXVECTOR3 pos)
{
	D3DXVECTOR3 center((float)_Width/2,(float)_Height/2,0);
	RECT srect;
	
	if(_Index < _SpritePerRow )
	{
		srect.left = (_Index % _SpritePerRow)*(_Width);
		srect.top = 0;
	}else
	{
		srect.left = ((_Index - _SpritePerRow) % _SpritePerRow)*(_Width);
		srect.top = (_Index / _SpritePerRow)*(_Height);
	}
	srect.right = srect.left + _Width;
	srect.bottom = srect.top + _Height;
	spritehandle->Draw(
		_Image->GetTexture(),
		&srect,
		&center,
		&pos,
		D3DCOLOR_XRGB(255,255,255)
		);
}

void Sprite::Next()
{
	_Index = _Index ++;
}
void Sprite::Reset()
{
	_Index = 0;
}
Sprite::~Sprite()
{
	_Image->~Texture();
	_Image = NULL;
}
