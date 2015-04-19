#pragma once
#include "GameObj.h"
#include <stdio.h>
#include <iostream>
#include <math.h>
#include <limits.h>
#include <vector>
#include "DynamicObj.h"
using namespace std;
class ColManager
{
public:

	RECT GetSweptBroadphaseBox(CGameObj* b, float t)
	{
		RECT broadphasebox;
		/*broadphasebox.left = b->_Vx > 0 ? b->_Bound.left  : b->_Bound.left + b->_Vx*t ;
		broadphasebox.top = b->_Vy > 0 ? b->_Bound.top : b->_Bound.top + b->_Vy*t ;
		broadphasebox.right = (b->_Vx > 0 ? b->_Vx*t + b->_Bound.right  : b->_Bound.right - b->_Vx*t )  ;
		broadphasebox.bottom =  (b->_Vy  > 0 ?   b->_Bound.bottom - b->_Vy*t : b->_Bound.bottom + b->_Vy*t );*/
		broadphasebox.left = b->_Vx > 0 ? b->_Bound.left  : b->_Bound.left + b->_Vx ;
		broadphasebox.top = b->_Vy > 0 ? b->_Bound.top : b->_Bound.top + b->_Vy ;
		broadphasebox.right = (b->_Vx > 0 ? b->_Vx + b->_Bound.right  : b->_Bound.right - b->_Vx )  ;
		broadphasebox.bottom =  (b->_Vy  > 0 ?   b->_Bound.bottom - b->_Vy : b->_Bound.bottom + b->_Vy );
		return broadphasebox;
	}
	bool AABBCheck(RECT b1, RECT b2)
	{
		return !(b1.right < b2.left || b1.left > b2.right || b1.bottom > b2.top || b1.top < b2.bottom);
	}
	bool AABB(RECT b1, RECT b2, float& moveX, float& moveY)
	{
		moveX = moveY = 0.0f;

		float l = b2.left - b1.right;
		float r = b2.right - b1.left;
		float t = - b2.top + b1.bottom;
		float b = - b2.bottom + b1.top;

		// check that there was a collision
		if (l > 0 || r < 0 || t > 0 || b < 0)
			return false;

		// find the offset of both sides
		moveX = abs(l) < r ? l : r;
		moveY = abs(t) < b ? t : b;

		// only use whichever offset is the smallest
		if (abs(moveX) < abs(moveY))
			moveY = 0.0f;
		else
			moveX = 0.0f;

		return true;
	}
	float SweptAABB(CGameObj* b1, CGameObj* b2, float& normalx, float& normaly, float t)
	{
		float v1x;
		float xInvEntry, yInvEntry;
		float xInvExit, yInvExit;
		float v1y = (b1->_Vy  - b2->_Vy );
		if(b1->_Vy < 0 && b2->_Vy > 0)
			v1y = -(b2->_Vy - b1->_Vy);
		if(b1->_Vy * b2->_Vy == 0)
		{
			v1x = b1->_Vx - b2->_Vx;
			if(b1->_Vx > 0 && b2->_Vx > 0 )
				v1x = abs(b1->_Vx - b2->_Vx);
			else if(b1->_Vx < 0 && b2->_Vx < 0)
				v1x = -abs(b1->_Vx - b2->_Vx);
			else if(b1->_Vx > 0 && b2->_Vx < 0)
				v1x = abs(b1->_Vx) + abs(b2->_Vx);
			else if(b1->_Vx < 0 && b2->_Vx > 0)
				v1x = -(abs(b1->_Vx) + abs(b2->_Vx));
		}
		else
		{
			float v1 = sqrt(b1->_Vx*b1->_Vx + b1->_Vy*b1->_Vy );
			float v2 = sqrt(b2->_Vx*b2->_Vx + b2->_Vy*b2->_Vy);
			v1x = v1 - v2;
		}



		// find the distance between the objects on the near and far sides for both x and y
		if (v1x > 0.0f)
		{
			xInvEntry = b2->_Bound.left - b1->_Bound.right;
			xInvExit = b2->_Bound.right - b1->_Bound.left;
		}
		else 
		{
			xInvEntry = (b2->_Bound.right) - b1->_Bound.left;
			xInvExit = b2->_Bound.left - (b1->_Bound.right);
		}

		if (v1y > 0.0f)
		{		
			yInvEntry = b2->_Bound.bottom - b1->_Bound.top;
			yInvExit = b2->_Bound.top - b1->_Bound.bottom;
		}
		else
		{
			yInvEntry = b2->_Bound.top - b1->_Bound.bottom;
			yInvExit = b2->_Bound.bottom - b1->_Bound.top;

		}
		float xEntry, yEntry;
		float xExit, yExit;

		if (v1x == 0.0f)
		{
			xEntry = -std::numeric_limits<float>::infinity();
			xExit = std::numeric_limits<float>::infinity();
		}
		else
		{
			xEntry = xInvEntry / v1x;
			xExit = xInvExit / v1x;
		}

		if (v1y == 0.0f)
		{
			yEntry = -std::numeric_limits<float>::infinity();
			yExit = std::numeric_limits<float>::infinity();
		}
		else
		{
			yEntry = yInvEntry / v1y;
			yExit = yInvExit / v1y;
		}
		float entryTime = xEntry>yEntry?xEntry:yEntry;
		float exitTime = xExit < yExit? xExit : yExit;

		if (entryTime > exitTime || xEntry < 0.0f && yEntry < 0.0f || xEntry > 1.0f || yEntry > 1.0f)
		{
			normalx = 0.0f;
			normaly = 0.0f;
			return 1.0f;
		}
		else // if there was a collision
		{        		
			// calculate normal of collided surface
			if (xEntry > yEntry)
			{
				if (xInvEntry > 0.0f)
				{
					normalx = 1.0f;
					normaly = 0.0f;
				}
				else
				{
					normalx = -1.0f;
					normaly = 0.0f;
				}
			}
			else
			{
				if (yInvEntry <= 0.0f)
				{
					normalx = 0.0f;
					normaly = 1.0f;
				}
				else
				{
					normalx = 0.0f;
					normaly = -1.0f;
				}
			}
			return entryTime;
		}
	}
	// return the time of collision
	int Intesected(RECT rec1, RECT rec2)
	{
		if(rec1.left <= rec2.left && rec1.right >= rec2.left || rec1.left >= rec2.left && rec1.left <= rec2.right)
		{
			if(rec1.top >= rec2.top && rec1.bottom <= rec2.top || rec1.top >= rec2.bottom && rec1.top <= rec2.top)
			{
				return 1;
			}
		}
		//if(rec1->_Bound.right < rec2->_Bound.left && )
		return 0;

	}


};