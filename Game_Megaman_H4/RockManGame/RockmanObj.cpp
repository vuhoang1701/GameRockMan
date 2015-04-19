#include "RockmanObj.h"
#include "ObjectManager.h"

CRockmanObj::CRockmanObj(void)
{
}

CRockmanObj::CRockmanObj(int id, int x, int y, Sprite* spr, float velx, float vely, float time, HWND hwnd, LPDIRECT3DDEVICE9 d3ddev):DynamicObj(id, x, y, spr, velx, vely)
{
	_sprJump = new Sprite(d3ddev, "..\\Data\\Megaman_Jump.png",32,24,12,6);
	_input = new Input(hwnd);
	onGround = false;
	timerun = time;
	countdelay = 0;
	delay = 0;
	accelerator = 0.05f;
	gravity = - 0.09; 
	_Vx = velx;
	_Vy = gravity;
	_Pos.x = x;
	_Pos.y = y;
	canMoveRight = true;
	canMoveLeft = true;
	canMoveUp = false;
};
void CRockmanObj::SetVeloc(int velx, int vely)
{
	this->_Vx = velx;
	this->_Vy = vely;
	_Vx = velx;
	_Vy = vely;
}
D3DXVECTOR2 CRockmanObj::GetVeloc()
{
	D3DXVECTOR2 a(this->_Vx, this->_Vy);
	return a;
}
void CRockmanObj::Update(CCamera *Cam, float time)
{
	_input->Update();
	float deltatime = (time - timerun);
	if(deltatime > 30)
	{
		timerun = time;
		if(onGround)
			_Vy = 0;
		else
		{
			_Vy +=	gravity*(deltatime);
		}
		_Pos.y += _Vy;		
		ProcessInput(deltatime);
		UpdatePosition(Cam,deltatime);
	}


	
}

void CRockmanObj::ProcessInput(float deltatime)
{
	if(_input->GetKeyState(DIK_ESCAPE))
		PostQuitMessage(0);
	if (_input->GetKeyState(DIK_L) && onGround == true)
	{
		if (_Dir == Direction::left)
		{
			this->_Vx = 1;
		}
		_Dir = Direction::right;
		canMoveLeft = true;
		if(++delay - countdelay >2)
		{
			delay = 0;	
			if(++this->_Spr->_Index > 5)
				this->_Spr->_Index = 3;

		}
		if (canMoveRight)
		{
			_Vx += accelerator* deltatime;
			if (_Vx > 7)
			{
				_Vx = 7;
			}
			if (_Pos.x <= 0)
			{
				_Pos.x = 0;
			}
			else
				this->_Pos.x += this->_Vx;
		}

	}
	else if(_input->GetKeyState(DIK_L) && onGround == false)
	{
		_Vx += accelerator* deltatime;
		if (_Vx > 7)
		{
			_Vx = 7;
		}
		this->_Pos.x += this->_Vx;
		_Dir = Direction::right;
	}
	else if (_input->GetKeyState(DIK_J))
	{
		if (_Dir == Direction::right)
		{
			_Vx = 1;
		}
		else
		{
			_Vx += accelerator* deltatime * -1;
			if (_Vx < -7)
			{
				_Vx = -7;
			}
			this->_Pos.x += this->_Vx;

		}
		_Dir = Direction::left;
		canMoveRight = true;
		if(++delay - countdelay > 2)
		{
			delay = 0;
			if(--this->_Spr->_Index < 6)
				this->_Spr->_Index = 8;
		}
	}
	else if (_input->GetKeyState(DIK_I) && canMoveUp == true)
	{			
		_Dir = up;
		if(++delay>countdelay)
		{
			delay = 0;
			if(--this->_Spr->_Index < 6)
				this->_Spr->_Index = 7;
		}
		_Vy = 4;
	}
	else if (_input->GetKeyState(DIK_K))
	{
		_Dir = down;
		if(++delay>countdelay)
		{
			delay = 0;
			if(--this->_Spr->_Index < 5)
				this->_Spr->_Index = 7;
		}
		_Vy = -4;
	}
	else
	{

		if(++delay - countdelay>70)
		{
			delay = 0;
			if(++this->_Spr->_Index > 1)
				this->_Spr->_Index = 0;
		}
	}
	//============================================
	if( _input->GetKeyDown() == (DIK_SPACE) && onGround== true)
	{
		_Vy = 20;
		_Pos.y += 4;
		onGround = false;
	}


}

void CRockmanObj::UpdatePosition(CCamera* cam, float t)
{
	
	cam->Update(_Pos.x,_Pos.y,t);
	_Bound.top		= _Pos.y + (_Spr->_Height/2);
	_Bound.bottom	= _Pos.y - (_Spr->_Height/2);
	_Bound.left		= _Pos.x - (_Spr->_Width/2);
	_Bound.right	= _Pos.x + (_Spr->_Width/2);
}

void CRockmanObj::AnsCol(vector<CGameObj*> List, float t)
{
#pragma region va chạm trên
	if(ColTop.size() > 0){
		for(map<int,float>::iterator i = ColTop.begin();i != ColTop.end();++i)
		{
			RECT rect = CObjectManager::GetRectClip(this->GetBound(),List[(*i).first]->GetBound());
			int height = rect.top - rect.bottom;
			if (height > 0)
			{
				int a = 1;
				switch (List[(*i).first]->_Id)
				{
						case 0: case 1: case 2:					// thanh bar
							onGround = true;
							_Pos.y += ((*i).second * _Vy  ) ;
							_Pos.x += (*i).second * _Vx ;
							_Bound.top		= _Pos.y + (_Spr->_Height/2);
							_Bound.bottom	= _Pos.y - (_Spr->_Height/2);
							_Bound.left		= _Pos.x - (_Spr->_Width/2);
							_Bound.right	= _Pos.x + (_Spr->_Width/2);
							break;
				}
	
			}
		}
	}
	else
	{
		onGround = false;
	}
#pragma endregion
#pragma region va chạm dưới
	for(int i = 0; i < ColBot.size();i++)
	{
		RECT rect = CObjectManager::GetRectClip(this->GetBound(),List[ColBot[i]]->GetBound());
		int height = rect.top - rect.bottom;
		switch (List[ColBot[i]]->_Id)
		{
		case 0: case 1: case 2:   //bar
			{
				canMoveUp = false;
				if ( height < 5)
				{
					this->_Pos.y += height; 
				}
			}
			break;
		}
	}
#pragma endregion
#pragma region va chạm trái
	for(int i = 0; i < ColLeft.size();i++)
	{
		RECT rect = CObjectManager::GetRectClip(this->GetBound(),List[ColLeft[i]]->GetBound());
		int width = rect.right - rect.left;
		if(width > 5)
		{
			int a = 1;
		}
		switch (List[ColLeft[i]]->_Id)
		{
		case 0: case 1: case 2:   //bar
			{
				if (this->_Bound.bottom <= List[ColLeft[i]]->_Bound.bottom)
				{
					canMoveRight = false;
					/*if ( width < 5)
					{
						this->_Pos.x -= width; 
					}*/
				}
				else canMoveRight = true;
			}
			break;
		}
	}
#pragma endregion
#pragma region va chạm phải
	for(int i = 0; i < ColRight.size();i++)
	{
		switch (List[ColRight[i]]->_Id)
		{
		case 0: case 1: case 2:   //bar
			{
				if (this->_Bound.left >= List[ColRight[i]]->_Bound.right && this->_Bound.bottom <= List[ColRight[i]]->_Bound.bottom)
				{
					canMoveLeft = false;
				}

			}
			break;
		}
	}
#pragma endregion
#pragma region đang va chạm
	for(int i = 0; i < Colding.size();i++)
	{
		switch (List[Colding[i]]->_Id)
		{
			
		case 0: case 1: case 2:					// thanh bar
			
			_Pos.y = List[Colding[i]]->_Bound.bottom - (_Bound.top - _Bound.bottom)/2;
			if(_Pos.y < List[Colding[i]]->_Pos.y)
			{
				_Pos.y = List[Colding[i]]->_Bound.top + (_Bound.top - _Bound.bottom)/2;
				onGround = true;
			}
			else 
			{
				_Pos.y = List[Colding[i]]->_Bound.bottom - (_Bound.top - _Bound.bottom)/2;
				onGround = false;
			}
			break;
		}
	}
#pragma endregion
#pragma region xóa các list xử lí va chạm
	ColBot.clear();
	Colding.clear();
	ColTop.clear();
	ColLeft.clear();
	ColRight.clear();
#pragma endregion
}

CRockmanObj::~CRockmanObj(void)
{
}
