#pragma once
#include "Sprite.h"
#include <d3d9.h>
#include <d3dx9.h>
#include "Camera.h"
class CGameObj
{
protected:
	
	
public:
	int _Id;
	Sprite *_Spr;
	bool _isAlive;
	float _Vx;
	bool _isDead;
	float _Vy;
	RECT _Bound;
	D3DXVECTOR2 _Pos;
	CGameObj(void);
	virtual void Update(float t) = 0;
	CGameObj(int, int, int, Sprite*);
	void Render(LPD3DXSPRITE, CCamera*);
	RECT* GetBound();
	
	~CGameObj(void);
};

