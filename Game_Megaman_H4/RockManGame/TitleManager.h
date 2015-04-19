#pragma once
#include <vector>
#include "Title.h"
using namespace std;

class TitleManager
{
protected:
	Sprite *sprite;
	
	
public:
	int mapTitle[74][272];
	vector<Title *> listTitle;
	TitleManager(Sprite *,vector<Title *> );
	void InitListTitle(LPDIRECT3DDEVICE9 d3ddev);
	void CreateListTitle();
	void Update();
	void Render(LPD3DXSPRITE spritehandle, CCamera * cam);
	TitleManager(void);
	~TitleManager(void);
};

