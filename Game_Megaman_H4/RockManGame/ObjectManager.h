#pragma once
#include "CCollision.h"
#include "RockmanObj.h"
#include "CSingleton.h"
class CObjectManager : public CSingleton<CObjectManager>
{
	ColManager* col;
public:
	CObjectManager(){col = new ColManager();}
	void CheckForRockMan(CRockmanObj* RockMan,vector<CGameObj*> List,long t)
	{
		float norx,nory;
		float collisiontime = 1;
		for(int j = 0; j < List.size(); j++)
		{
			if(col->AABBCheck(RockMan->_Bound,List[j]->_Bound) == false)
				{
					RECT broadphrasebox = col->GetSweptBroadphaseBox(RockMan, t);
					if(col->AABBCheck(broadphrasebox,List[j]->_Bound))
					{
					    collisiontime = col->SweptAABB(RockMan,List[j],norx,nory, t);
						if(collisiontime > 0 && collisiontime < 1.0f && List[j]->_isDead == false)
						{
							if(norx == 1 && RockMan->_isDead == false)
							{
								RockMan->ColLeft.push_back(j);
								
							}
							else if(norx == -1 && RockMan->_isDead == false)
							{
								RockMan->ColRight.push_back(j);
							}
							else if(nory == 1 && RockMan->_isDead == false /*&& RockMan->_transform == false*/)
							{
								RockMan->ColTop[j] = collisiontime;
								
							}
							else if(nory == -1 && RockMan->_isDead == false /*&& RockMan->_transform == false*/)
							{
								RockMan->ColBot.push_back(j);
							}
							
						}
					}
				}
			else
			{
				RockMan->Colding.push_back(j);	
			}
		}
		RockMan->AnsCol(List, t);
	}
	
	void UpdateList(vector<CGameObj*> &List,long t)
	{
		for(int i = 0; i < List.size();i++)
		{
			if(List[i]->_isDead == false)
				List[i]->Update(t);
		}
		for(int i = 0; i < List.size();i++)
		{
			if(List[i]->_Pos.y < -35)
				List[i]->_isDead = true;
			if(List[i]->_isDead == true)
			{
				List[i]->_isDead = true;
				List.erase(List.begin() + i );
				
			}
				
		}
		
		
	}
	void Render(vector<CGameObj*> List,LPD3DXSPRITE spritehandle,CCamera* Cam)
	{
		/*for(int i = 0; i < List.size();i++)
			if(List[i]->id != 16 && List[i]->id != 13 && List[i]->id != 16 && List[i]->id != 17 && List[i]->id != 36 )
				List[i]->Render(spritehandle,Cam);
		for(int i = 0; i < List.size();i++)
			if(List[i]->id == 16 && List[i]->id == 13 && List[i]->id == 16 && List[i]->id == 17 && List[i]->id != 36 )
				List[i]->Render(spritehandle,Cam);*/
		for(int i = 0; i < List.size();i++)
			if(List[i]->_isDead == false )
				List[i]->Render(spritehandle,Cam);
		
	}

	static int Clip(RECT* object1, RECT* object2)
	{
		LPRECT result = new RECT();
		IntersectRect(result, object2, object1);
		if(result->left != 0 || result->right != 0 || result->bottom != 0 || result->top != 0)
		{
			return 1;
		}
		return 0;
	}

	static RECT GetRectClip(RECT* object1, RECT* object2)
	{
		/*RECT result;
		if (Clip(object1,object2))
		{
			if (object1->left <= object2->left )
			{
				result.left = object2->left;
			} 
			else
			{
				result.left = object1->left;
			}
			if (object1->top < object2->top)
			{
				result.top = object1->top;
			} 
			else
			{
				result.top = object1->top;
			}
			if (object1->bottom < object2->bottom)
			{
				result.bottom = object2->bottom;
			} 
			else
			{
				result.bottom = object1->bottom;
			}
		} 
		else
		{
		}
		
		return result;*/
		return RECT();
	}
};

