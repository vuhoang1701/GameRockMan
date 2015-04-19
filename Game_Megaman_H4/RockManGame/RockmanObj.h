#pragma once
#include "DynamicObj.h"
#include "dxinput.h"
#include <vector>
#include <map>



class CRockmanObj:public DynamicObj
{
private:
	Input* _input;  // xu ly input
	Sprite* _sprJump; //sprite cho nhay, leo cau thang
protected:
	int countdelay;
	int delay;
	int timerun;
	float gravity;              // gia toc trong truong
	float accelerator;			// gia toc
	bool onGround;
	bool canMoveLeft;  // xac dinh rockman co dc di qua trai hay khong
	bool canMoveRight; // xac dinh rockman co dc di qua phai hay ko
	bool canMoveUp;    // xac dinh rockman co dc di len tren hay ko
public:
	CRockmanObj(void);
	CRockmanObj(int id, int x, int y, Sprite* spr, float velx, float vely, float time, HWND hwnd, LPDIRECT3DDEVICE9);
	vector<int> ColBot,  ColRight, ColLeft, Colding; //danh sach cac vi tri trong list de su li va cham
	map<int,float> ColTop; // va cham tren
	void AnsCol(vector<CGameObj*>, float); // Xu ly va cham
	void SetVeloc(int velx, int vely);
	D3DXVECTOR2 GetVeloc();
	void Update(CCamera*, float time);
	void UpdatePosition(CCamera*, float );
	void ProcessInput(float);
	~CRockmanObj(void);
};

