//
// ModuleImage.cpp for cpp_spider in sources/client/modules
//
// Made by Benoit Hamon
// Login   <benoit.hamon@epitech.eu>
//
// Started on  Thu Oct 05 10:32:15 2017 Benoit Hamon
// Last update Thu Oct 05 11:02:34 2017 Benoit Hamon
//


#include "ModuleImage.hpp"

#include <Windows.h>
#include <gdiplus.h>
using namespace Gdiplus;

int GetEncoderClsid(const WCHAR* format, CLSID* pClsid)
{
    UINT  num = 0;          // number of image encoders
    UINT  size = 0;         // size of the image encoder array in bytes

    ImageCodecInfo* pImageCodecInfo = NULL;

    GetImageEncodersSize(&num, &size);
    if(size == 0)
        return -1;  // Failure

    pImageCodecInfo = (ImageCodecInfo*)(malloc(size));
    if(pImageCodecInfo == NULL)
        return -1;  // Failure

    GetImageEncoders(num, size, pImageCodecInfo);

    for(UINT j = 0; j < num; ++j)
    {
        if( wcscmp(pImageCodecInfo[j].MimeType, format) == 0 )
        {
            *pClsid = pImageCodecInfo[j].Clsid;
            free(pImageCodecInfo);
            return j;  // Success
        }
    }
    free(pImageCodecInfo);
    return -1;  // Failure
}

int main() {

// get the device context of the screen
    HDC hScreenDC = CreateDC("DISPLAY", NULL, NULL, NULL);
// and a device context to put it in
    HDC hMemoryDC = CreateCompatibleDC(hScreenDC);

    int width = GetDeviceCaps(hScreenDC, HORZRES);
    int height = GetDeviceCaps(hScreenDC, VERTRES);

// maybe worth checking these are positive values
    HBITMAP hBitmap = CreateCompatibleBitmap(hScreenDC, width, height);

// get a new bitmap
    HBITMAP hOldBitmap = (HBITMAP) SelectObject(hMemoryDC, hBitmap);

    BitBlt(hMemoryDC, 0, 0, width, height, hScreenDC, 0, 0, SRCCOPY);
    hBitmap = (HBITMAP) SelectObject(hMemoryDC, hOldBitmap);

// clean up
    DeleteDC(hMemoryDC);
    DeleteDC(hScreenDC);


    GdiplusStartupInput gdiplusStartupInput;
    ULONG_PTR gdiplusToken;
    GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

    //HBITMAP hBitmap = (HBITMAP)LoadImage(GetModuleHandle(NULL), "babe.bmp", IMAGE_BITMAP, 0,0, LR_LOADFROMFILE);
    Bitmap *image = new Bitmap(hBitmap, NULL);

    CLSID myClsId;
    int retVal = GetEncoderClsid(L"image/bmp", &myClsId);

    image->Save(L"output.bmp", &myClsId, NULL);
    delete image;

    GdiplusShutdown(gdiplusToken);
    return 0;
}
