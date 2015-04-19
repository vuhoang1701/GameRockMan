#pragma once
#include "GameObj.h"
#include "Camera.h"
using namespace std;


class DynamicObj :
	public CGameObj
{
protected:
	
	
	float	m_velocX;
	float	m_velocY;

public:
	virtual void SetVeloc(float x,float y);
	virtual D3DXVECTOR2 GetVeloc();
	Direction _Dir;
	DynamicObj(int id,float x,float y,Sprite* sprite,float Vel_X,float Vel_y);
	DynamicObj(void);
	void Update(CCamera*, int time);
	void Update(float){};
	~DynamicObj(void);
};

