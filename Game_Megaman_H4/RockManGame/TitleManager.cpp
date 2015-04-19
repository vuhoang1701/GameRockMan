#include "TitleManager.h"
#include <iostream> 
#include <fstream> 
#include <iostream> 
#include <string>
#include <vector>
using namespace std;


void TitleManager::InitListTitle(LPDIRECT3DDEVICE9 d3ddev)
{
	int w = 272,h = 73,m = 0,n = 0;
	
	
	vector<vector<int >> arr;
	string line;
	ifstream file("State1_map.txt", ifstream::in);
	if(! file.is_open())
    {
        cout<<"Khong the mo file.n";
    }
    else 
	{
		while(!file.eof())
		{
			getline(file,line);
			const char* str_pattern = line.c_str();
			char* str = new char[strlen(str_pattern) + 1];
			strcpy(str, str_pattern);
			char *p = strtok(str, ",");
			while (p != NULL)
			{
				mapTitle[m][n] = atoi(p);
				p = strtok(NULL, ",");
				n++;
			}
			m++;
			n = 0;
		}
	}
	for (int i=0; i<66; i++)
	{
		
		Title *t1 = new Title();
		t1->id = i+1;
		t1->sprite = new Sprite(d3ddev,"..\\Data\\State1_bank.png",16,16,65,11,6);
		t1->sprite->_Index = i;
		listTitle.push_back(t1);
		
	}

	//Title *t1 = new Title();
	//t1->id = 5;
	//t1->sprite = new Sprite(d3ddev,"..\\Data\\State1_bank.png",16,16,66,11,6);
	//t1->sprite->_Index = 11;
	//Title *t2 = new Title();
	//t2->id = 6;
	//t2->sprite = new Sprite(d3ddev,"..\\Data\\State1_bank.png",16,16,66,11,6);
	//t2->sprite->_Index = 5;
	//Title *t3 = new Title();
	//t3->id = 7;
	//t3->sprite = new Sprite(d3ddev,"..\\Data\\State1_bank.png",16,16,66,11,6);
	//t3->sprite->_Index = 6;
	//Title *t4 = new Title();
	//t4->id = 8;
	//t4->sprite = new Sprite(d3ddev,"..\\Data\\State1_bank.png",16,16,66,11,6);
	//t4->sprite->_Index = 7;
	//Title *t5 = new Title();
	//t5->id = 9;
	//t5->sprite = new Sprite(d3ddev,"..\\Data\\State1_bank.png",16,16,66,11,6);
	//t5->sprite->_Index = 8;
	//Title *t6 = new Title();
	//t6->id = 4;
	//t6->sprite = new Sprite(d3ddev,"..\\Data\\State1_bank.png",16,16,66,11,6);
	//t6->sprite->_Index = 3;
	//
	//listTitle.push_back(t1);
	//listTitle.push_back(t2);
	//listTitle.push_back(t3);
	//listTitle.push_back(t4);
	//listTitle.push_back(t5);
	//listTitle.push_back(t6);
}

void TitleManager::Render(LPD3DXSPRITE spritehandle, CCamera * cam)
{
	
}
TitleManager::TitleManager(void)
{
	
}


TitleManager::~TitleManager(void)
{
}
