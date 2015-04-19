#pragma once
#include <d3dx9.h>
#include <d3d9.h>
class Surface
{
	LPDIRECT3DSURFACE9 _surface;
	LPDIRECT3DDEVICE9 _d3ddev;
	D3DXIMAGE_INFO _Image_info;
public:
	Surface(LPDIRECT3DDEVICE9);
	LPDIRECT3DSURFACE9 LoadSurface(char* );
	LPDIRECT3DSURFACE9 GetSurface();
	int GetHight();
	int GetWidth();
	~Surface(void);
};

