#include "RockmanObj.h"
#include "CGround.h"
#include <math.h>
#include <limits.h>
#include <stdio.h>
#include <iostream>
class CCollision
{
public:

	RECT GetSweptBroadphaseBox(CGameObj* b)
	{
		RECT broadphasebox;
		broadphasebox.left = b->_Vx > 0 ? b->_Bound.left  : b->_Bound.left + b->_Vx ;
		broadphasebox.top = b->_Vy > 0 ? b->_Bound.top : b->_Bound.top + b->_Vy ;
		broadphasebox.right = (b->_Vx > 0 ? b->_Vx + b->_Bound.right  : b->_Bound.right - b->_Vx )  ;
		broadphasebox.bottom =  (b->_Vy  > 0 ?   b->_Bound.bottom - b->_Vy : b->_Bound.bottom + b->_Vy );
		return broadphasebox;
	}
	bool AABBCheck(RECT b1, RECT b2)
	{
		bool check = Intesected(b1,b2); 
		return check;
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
	float SweptAABB(CGameObj* b1, CGameObj* b2, float& normalx, float& normaly)
	{
		
		float xInvEntry, yInvEntry;
		float xInvExit, yInvExit;
		// find the distance between the objects on the near and far sides for both x and y
		if (b1->_Vx > 0.0f)
		{
			xInvEntry = b2->_Bound.left - b1->_Bound.right;
			xInvExit = b2->_Bound.right - b1->_Bound.left;
		}
		else 
		{
			xInvEntry = (b2->_Bound.right) - b1->_Bound.left;
			xInvExit = b2->_Bound.left - (b1->_Bound.right);
		}

		if (b1->_Vy > 0.0f)
		{		
			yInvEntry = b2->_Bound.bottom - b1->_Bound.top;
			yInvExit = b2->_Bound.top - b1->_Bound.bottom;
		}
		else
		{
			yInvEntry = b2->_Bound.top - b1->_Bound.bottom;
			yInvExit = b2->_Bound.bottom - b1->_Bound.top;

		}
		 // find time of collision and time of leaving for each axis (if statement is to prevent divide by zero)
		float xEntry, yEntry;
		float xExit, yExit;

		if (b1->_Vx == 0.0f)
		{
			xEntry = -std::numeric_limits<float>::infinity();
			xExit = std::numeric_limits<float>::infinity();
		}
		else
		{
			xEntry = xInvEntry / b1->_Vx;
			xExit = xInvExit / b1->_Vx;
		}

		if (b1->_Vy == 0.0f)
		{
			yEntry = -std::numeric_limits<float>::infinity();
			yExit = std::numeric_limits<float>::infinity();
		}
		else
		{
			yEntry = yInvEntry / b1->_Vy;
			yExit = yInvExit / b1->_Vy;
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
			if(rec1.top >= rec2.top && rec1.bottom <= rec2.top || rec1.top >= rec2.bottom && rec1.bottom <= rec2.bottom)
			{
				return 1;
			}
		}
		else if(rec2.left <= rec1.left && rec2.right >= rec1.left || rec2.left >= rec1.left && rec2.left <= rec1.right)
		{
			if(rec2.top >= rec1.top && rec2.bottom <= rec1.top || rec2.top >= rec1.bottom && rec2.top <= rec1.bottom)
			{
				return 1;
			}
		}

		return 0;

	}
};