#pragma once
#include <d3dx9.h>
#include <d3d9.h>
class Texture
{
protected:
	LPDIRECT3DTEXTURE9 _texture;
	D3DXIMAGE_INFO _image_info;
	LPDIRECT3DDEVICE9 _d3ddev;
public:
	void GetDevice(LPDIRECT3DDEVICE9 );
	Texture(LPDIRECT3DDEVICE9);
	LPDIRECT3DTEXTURE9 LoadTexture(char*, D3DCOLOR);
	LPDIRECT3DTEXTURE9 LoadTexture(char*, D3DCOLOR,int,int);
	LPDIRECT3DTEXTURE9 GetTexture();
	int GetHeight();
	int GetWidth();
	~Texture();
};

