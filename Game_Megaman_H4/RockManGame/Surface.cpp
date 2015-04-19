#include "Surface.h"


Surface::Surface(LPDIRECT3DDEVICE9 d3ddev)
{
	this->_surface = NULL;
	this->_d3ddev = d3ddev;
}
LPDIRECT3DSURFACE9 Surface::LoadSurface(char* filename)
{
    HRESULT result;
    
    //get width and height from bitmap file
    result = D3DXGetImageInfoFromFile(filename, &_Image_info);
    if (result != D3D_OK)
        return NULL;

    //create surface
    result = _d3ddev->CreateOffscreenPlainSurface(
		_Image_info.Width,         //width of the surface
		_Image_info.Height,        //height of the surface
        D3DFMT_X8R8G8B8,    //surface format
        D3DPOOL_DEFAULT,    //memory pool to use
		&_surface,             //pointer to the surface
        NULL);              //reserved (always NULL)

    if (result != D3D_OK)
        return NULL;

    //load surface from file into newly created surface
    result = D3DXLoadSurfaceFromFile(
		_surface,              //destination surface
        NULL,               //destination palette
        NULL,               //destination rectangle
        filename,           //source filename
        NULL,               //source rectangle
        D3DX_DEFAULT,       //controls how image is filtered
        0,         //for transparency (0 for none)
        NULL);              //source image info (usually NULL)

    //make sure file was loaded okay
    if (result != D3D_OK)
        return NULL;

	return _surface;
}
LPDIRECT3DSURFACE9 Surface::GetSurface()
{
	return _surface;
}
int Surface::GetHight()
{
	return _Image_info.Height;
}
int Surface::GetWidth()
{
	return _Image_info.Width;
}
Surface::~Surface(void)
{
	_surface->Release();
}

