#pragma once
#include <d3d9.h>
#include<d3dx9.h>
#include "dxinput.h"
#include "Sprite.h"
#include "Surface.h"
#include "TitleManager.h"
#include "CGround.h"
#include "ObjectManager.h"
using namespace std;
#define SCREEN_HEIGHT 224
#define SCREEN_WIDTH 256
#define NAME "ROCKMAN GAME"
class CGame
{ 
private:
	Input* _input;
	CObjectManager* collisionManager;
	vector<CGameObj*> listObjectDemo;
	TitleManager *t;
	Texture* back;
	CRockmanObj* rm;
	Sprite *spr;
	int _size;
	HWND hwnd;
	LPDIRECT3D9 d3d;
	LPDIRECT3DDEVICE9 d3ddev;
	LPD3DXSPRITE sprite_handle;
	LPDIRECT3DSURFACE9 backbuffer;
public:
	CGameObj* obj;
	CCamera* Cam;
	CCamera* GetCam();
	CGame(void);
	void LoadResource(Sprite);
	HWND GetWindowHandle();
	LPDIRECT3DDEVICE9 GetD3DDevice();
	LPD3DXSPRITE GetSpriteHandle();
	bool Init_Direct3D();
	bool Init_Window(HINSTANCE);
	static LRESULT CALLBACK	WinProc(HWND, UINT, WPARAM, LPARAM);
	int Game_Init();
	void Game_Run();
	void Game_End();
	~CGame(void);
};

