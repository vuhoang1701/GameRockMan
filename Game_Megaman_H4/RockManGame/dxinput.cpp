#include "dxinput.h"

Input::Input( HWND hwnd )
{

	//save window handle
	m_hWnd= hwnd;

	//create DirectInput object
	DirectInput8Create( GetModuleHandle(NULL), DIRECTINPUT_VERSION,IID_IDirectInput8, (void**)&di, NULL );

	//initialize keyboard
	di->CreateDevice(GUID_SysKeyboard, &keyboard, NULL);
	keyboard->SetDataFormat(&c_dfDIKeyboard );
	keyboard->SetCooperativeLevel( m_hWnd, 
		DISCL_FOREGROUND | DISCL_NONEXCLUSIVE );
	DIPROPDWORD dipdw;

	dipdw.diph.dwSize       = sizeof(DIPROPDWORD);
	dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER);
	dipdw.diph.dwObj        = 0;
	dipdw.diph.dwHow        = DIPH_DEVICE;
	dipdw.dwData            = KEYBOARD_BUFFER_SIZE; // Arbitary buffer size

	//    trace(L"SetProperty for keyboard successfully");

	keyboard->SetProperty( DIPROP_BUFFERSIZE, &dipdw.diph ); 
	keyboard->Acquire();

	
}

Input::~Input()
{
	di->Release();
	keyboard->Release();
	mouse->Release();
}

int Input::IsKeyDown(int KeyCode)
{
	return (keyState[KeyCode] & 0x80) > 0;
}
int Input::GetKeyDown()
{
	int tam = _KeyDown;
	_KeyDown = 0;
	return tam;
}
int Input::GetKeyUp()
{
	int tam = _KeyUP;
	_KeyUP = 0;
	return tam;
}

void Input::Update()
{
	//poll state of the keyboard
	keyboard->Poll();
	if (!SUCCEEDED(keyboard->GetDeviceState(256,(LPVOID)&keyState)))
	{
		//keyboard device lost, try to re-acquire
		keyboard->Acquire();
	}
	// Collect all buffered events
	DWORD dwElements = KEYBOARD_BUFFER_SIZE;
	HRESULT hr = keyboard->GetDeviceData( sizeof(DIDEVICEOBJECTDATA), KeyEvents, &dwElements, 0 );

	// Scan through all data, check if the key is pressed or released
	for( DWORD i = 0; i < dwElements; i++ ) 
	{
		int KeyCode = KeyEvents[i].dwOfs;
		int KeyState = KeyEvents[i].dwData;
		if ( (KeyState & 0x80) > 0)
			_KeyDown = KeyCode; 
		else 
			_KeyUP = KeyCode;
	}
	
}
