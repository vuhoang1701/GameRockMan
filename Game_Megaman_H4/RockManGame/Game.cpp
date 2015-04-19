#include "Game.h"


CGame::CGame(void)
{
	d3d = NULL;
	d3ddev = NULL;
	backbuffer = NULL;
	_input = new Input(hwnd);
}


CGame::~CGame(void)
{
	if(d3d)
		d3d->Release();
	if(d3ddev)
		d3ddev->Release();
	if(backbuffer)
		backbuffer->Release();
}

HWND CGame::GetWindowHandle()
{
	return hwnd;
}

LPD3DXSPRITE CGame::GetSpriteHandle()
{
	return sprite_handle;
}

LPDIRECT3DDEVICE9 CGame::GetD3DDevice()
{
	return d3ddev;
}
//=====================
bool CGame::Init_Window(HINSTANCE hInstance)
{
	// Register to windows
	WNDCLASS wndclass;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.hCursor = LoadCursor(NULL, IDI_APPLICATION);
	wndclass.hIcon = LoadIcon(NULL, IDC_ARROW);
	wndclass.hInstance = hInstance;
	wndclass.lpfnWndProc = WinProc;
	wndclass.lpszClassName = NAME;
	wndclass.lpszMenuName = NULL;
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	if (FAILED(RegisterClass(&wndclass)))
		return FALSE;

	// Create window
	hwnd = CreateWindow(NAME, 
		NAME,
		WS_OVERLAPPEDWINDOW,
		100,
		100,
		SCREEN_WIDTH,
		SCREEN_HEIGHT,
		NULL,
		NULL,
		hInstance,
		this
		);
	if (!hwnd)
		return FALSE;

	ShowWindow(hwnd, SW_SHOW);
	UpdateWindow(hwnd);
	return TRUE;
}

LRESULT CALLBACK CGame::WinProc(HWND m_hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(m_hWnd, iMessage, wParam, lParam);
}

//======================

bool CGame::Init_Direct3D()
{

	//initialize Direct3D
	d3d = Direct3DCreate9(D3D_SDK_VERSION);
	if (d3d == NULL)
	{
		MessageBox(hwnd, "Error initializing Direct3D", "Error", MB_OK);
		return 0;
	}

	//set Direct3D presentation parameters
	D3DPRESENT_PARAMETERS m_d3d_paramters; 
	ZeroMemory(&m_d3d_paramters, sizeof(m_d3d_paramters));

	m_d3d_paramters.Windowed = TRUE;
	m_d3d_paramters.SwapEffect = D3DSWAPEFFECT_COPY;
	m_d3d_paramters.BackBufferFormat = D3DFMT_X8R8G8B8;
	m_d3d_paramters.BackBufferCount = 1;
	m_d3d_paramters.BackBufferWidth = SCREEN_WIDTH;
	m_d3d_paramters.BackBufferHeight = SCREEN_HEIGHT;
	m_d3d_paramters.hDeviceWindow = hwnd;
	m_d3d_paramters.PresentationInterval = D3DPRESENT_INTERVAL_ONE;

	//create Direct3D device (software)
	d3d->CreateDevice(
		D3DADAPTER_DEFAULT, 
		D3DDEVTYPE_HAL, 
		hwnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&m_d3d_paramters, 
		&d3ddev);

	if (d3ddev == NULL)
	{
		return FALSE;
	}
	d3ddev->SetRenderState(D3DRS_LIGHTING, FALSE);
	d3ddev->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	D3DXCreateSprite(d3ddev, &sprite_handle);
	return TRUE;
}
//=================

int CGame::Game_Init()
{
	if(!Init_Direct3D())
	return 0;
	HRESULT hr = D3DXCreateSprite(d3ddev,&sprite_handle);
	if(hr != D3D_OK)
		return 0;
	back = new Texture(d3ddev);
	back->LoadTexture("..\\Data\\background.jpg",NULL, 1537, 224);
	t = new TitleManager();
	spr = new Sprite(d3ddev,"..\\Data\\Megaman_Run.png",30,30,12,6);
	t->InitListTitle(d3ddev);
	float now = GetTickCount();
	
	rm = new CRockmanObj(0,150,200,spr,3,0, now, hwnd, d3ddev);
	if(back->LoadTexture("..\\Data\\background.jpg",NULL, 1537, 224) == NULL)
		return 0;
	collisionManager = new CObjectManager();
	CGameObj* ground1 = new CGround(d3ddev,0, 0 , 60);
	listObjectDemo.push_back(ground1);
	for (int i = 0; i < 10; ++i)
	{
		CGameObj* ground = new CGround(d3ddev,i % 3, 0 + 16*i, 30);
		listObjectDemo.push_back(ground);
	}
	for (int i = 12; i < 60; ++i)
	{
		CGameObj* ground = new CGround(d3ddev,i % 3, 0 + 16*i, 50);
		listObjectDemo.push_back(ground);
	}

	for (int i = 60; i < 100; ++i)
	{
		CGameObj* ground = new CGround(d3ddev,i % 3, 0 + 16*i, 30);
		listObjectDemo.push_back(ground);
	}

	Cam = new CCamera();
	d3ddev->GetBackBuffer(0,0,D3DBACKBUFFER_TYPE_MONO,&backbuffer);
	return 1;
	
}
CCamera* CGame::GetCam()
{
	return Cam;
}
void CGame::Game_Run()
{
	MSG msg;
	int done = 0;
	   while(!done)
		{
			
		  if(PeekMessage(&msg,NULL,0,0,PM_REMOVE))
			{
				if(msg.message == WM_QUIT)
					done = 1;
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		  
			else
			{
				HRESULT hr = d3ddev->BeginScene();
				if(SUCCEEDED(hr))
					{
						float now = GetTickCount();
						d3ddev->Clear(0,NULL,D3DCLEAR_TARGET,D3DCOLOR_XRGB(0,255,255),1,0);
						D3DXVECTOR3 pos = Cam->GetPointTransform(0,224);
						sprite_handle->Begin(D3DXSPRITE_ALPHABLEND);
						rm->Update(Cam, now);
						collisionManager->CheckForRockMan(rm,listObjectDemo,now);
						Cam->Check(t->mapTitle, rm->_Dir);
						/*for(int i = 73 - Cam->_pos.y/16 ;i <= 73 - (Cam->_pos.y - Cam->_height)/16 + 1 ; ++i)
							for(int j = Cam->_pos.x/16 -1;j <=(Cam->_pos.x + Cam->_width)/16 + 1;j ++)
							{
								for(int k = 0;k < t->listTitle.size();k++)
								{
									if(t->mapTitle[i][j] == t->listTitle.at(k)->id)
									{
										t->listTitle.at(k)->x = j*16 ;
										t->listTitle.at(k)->y = 73*16 - i*16 + 8;
										t->listTitle.at(k)->Render(sprite_handle,Cam);
									}
								}
							}*/
							for (int i = 0; i < listObjectDemo.size();++i)
							{
								listObjectDemo[i]->Render(sprite_handle,Cam);
							}
					rm->Render(sprite_handle, Cam);
					sprite_handle->End();
						
						
					}
				
					d3ddev->EndScene();
					d3ddev->Present(NULL,NULL,NULL,NULL);
			  }
	
		
	}
		
}
void CGame::Game_End()
{

}