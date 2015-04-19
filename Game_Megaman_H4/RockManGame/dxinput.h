


#ifndef _INPUT_H
#define  _INPUT_H

#include <Windows.h>
//#include <d3d9.h>
//#include <d3dx9.h>
#include <dinput.h>


#define  KEYBOARD_BUFFER_SIZE 1024
class Input
{
	private:
		HWND m_hWnd; 
		IDirectInput8 *di; 
		IDirectInputDevice8 *keyboard;
		IDirectInputDevice8 *mouse;
		char keyState[256]; 
		DIMOUSESTATE MouseState;
		DIDEVICEOBJECTDATA KeyEvents[ KEYBOARD_BUFFER_SIZE ]; 
		int _KeyUP,_KeyDown;
		int _PreState[2];//1 down,2 up
		POINT position; 

	public:
		Input( HWND window );
		virtual ~Input();
		void Update();
		//key
		char GetKeyState(int key) { return keyState[key]; }
		int IsKeyDown(int);
		int GetKeyDown();
		int GetKeyUp();

		

		

};
#endif