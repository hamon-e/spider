//
// ModuleImage.cpp for cpp_spider in sources/client/modules
//
// Made by Benoit Hamon
// Login   <benoit.hamon@epitech.eu>
//
// Started on  Thu Oct 05 10:32:15 2017 Benoit Hamon
// Last update Fri Oct 06 21:33:45 2017 Benoit Hamon
//

#include <Windows.h>
#include <gdiplus.h>

#include "ModuleImage.hpp"

bool GetEncoderClsid(std::string const &format, CLSID* pClsid) {
    int num = 0;
    int size = 0;

    ImageCodecInfo* pImageCodecInfo = NULL;

    GetImageEncodersSize(&num, &size);
    if (size == 0)
        return false;

    pImageCodecInfo = (ImageCodecInfo*)(malloc(size));
    if (!pImageCodecInfo)
        return false;

    GetImageEncoders(num, size, pImageCodecInfo);

    for (int j = 0; j < num; ++j) {
        if (wcscmp(pImageCodecInfo[j].MimeType, format) == 0) {
	    *pClsid = pImageCodecInfo[j].Clsid;
            ::free(pImageCodecInfo);
            return true;
        }
    }
    ::free(pImageCodecInfo);
    return false;
}

int main() {
    HDC hScreenDC = CreateDC("DISPLAY", NULL, NULL, NULL);
    HDC hMemoryDC = CreateCompatibleDC(hScreenDC);

    int width = GetDeviceCaps(hScreenDC, HORZRES);
    int height = GetDeviceCaps(hScreenDC, VERTRES);

    HBITMAP hBitmap = CreateCompatibleBitmap(hScreenDC, width, height);
    HBITMAP hOldBitmap = (HBITMAP) SelectObject(hMemoryDC, hBitmap);

    BitBlt(hMemoryDC, 0, 0, width, height, hScreenDC, 0, 0, SRCCOPY);
    hBitmap = (HBITMAP) SelectObject(hMemoryDC, hOldBitmap);

    DeleteDC(hMemoryDC);
    DeleteDC(hScreenDC);

    Gdiplus::GdiplusStartupInput gdiplusStartupInput;
    ULONG_PTR Gdiplus::gdiplusToken;
    Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

    Bitmap *image = new Bitmap(hBitmap, NULL);

    CLSID myClsId;
    int retVal = GetEncoderClsid("image/bmp", &myClsId);

    image->Save(L"output.bmp", &myClsId, NULL);
    delete image;

    Gdiplus::GdiplusShutdown(gdiplusToken);
    return 0;
}
