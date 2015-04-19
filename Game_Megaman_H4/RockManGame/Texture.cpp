#include "Texture.h"


Texture::Texture(LPDIRECT3DDEVICE9 d3ddev)
{
	_d3ddev = d3ddev;
	_texture = NULL;
}

LPDIRECT3DTEXTURE9 Texture::LoadTexture(char* filename,D3DCOLOR transcolor)
{
    HRESULT result;
    
    //get width and height from bitmap file
	result = D3DXGetImageInfoFromFile(filename, &_image_info);
    if (result != D3D_OK)
        return NULL;

    //create the new texture by loading a bitmap image file
	result = D3DXCreateTextureFromFileEx( 
        _d3ddev,              //Direct3D device object
        filename,            //bitmap filename
		_image_info.Width,          //bitmap image width
		_image_info.Height,         //bitmap image height
        1,                   //mip-map levels (1 for no chain)
        D3DPOOL_DEFAULT,     //the type of surface (standard)
        D3DFMT_UNKNOWN,      //surface format (default)
        D3DPOOL_DEFAULT,     //memory class for the texture
        D3DX_DEFAULT,        //image filter
        D3DX_DEFAULT,        //mip filter
        transcolor,          //color key for transparency
		&_image_info,               //bitmap file info (from loaded file)
        NULL,                //color palette
        &_texture );          //destination texture

    //make sure the bitmap textre was loaded correctly
    if (result != D3D_OK)
        return NULL;

    return _texture;
}

int Texture::GetHeight()
{
	return _image_info.Height;
}
LPDIRECT3DTEXTURE9 Texture::GetTexture()
{
	return _texture;
}
int Texture::GetWidth()
{
	return _image_info.Width;
}
Texture::~Texture()
{
	_texture->Release();
}

LPDIRECT3DTEXTURE9 Texture::LoadTexture(char* filename,D3DCOLOR transcolor,int width,int height)
{
	    HRESULT result;
    
    //get width and height from bitmap file
	result = D3DXGetImageInfoFromFile(filename, &_image_info);
    if (result != D3D_OK)
        return NULL;

    //create the new texture by loading a bitmap image file
	result = D3DXCreateTextureFromFileEx( 
        _d3ddev,              //Direct3D device object
        filename,            //bitmap filename
		width,          //bitmap image width
		height,         //bitmap image height
        1,                   //mip-map levels (1 for no chain)
        D3DPOOL_DEFAULT,     //the type of surface (standard)
        D3DFMT_UNKNOWN,      //surface format (default)
        D3DPOOL_DEFAULT,     //memory class for the texture
        D3DX_DEFAULT,        //image filter
        D3DX_DEFAULT,        //mip filter
        transcolor,          //color key for transparency
		&_image_info,               //bitmap file info (from loaded file)
        NULL,                //color palette
        &_texture );          //destination texture

    //make sure the bitmap textre was loaded correctly
    if (result != D3D_OK)
        return NULL;

    return _texture;
}

