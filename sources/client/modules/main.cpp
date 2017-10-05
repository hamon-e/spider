//
// main.cpp for cpp_spider in sources/client/modules
//
// Made by Benoit Hamon
// Login   <benoit.hamon@epitech.eu>
//
// Started on  Thu Oct 05 10:46:30 2017 Benoit Hamon
// Last update Thu Oct 05 11:02:54 2017 Benoit Hamon
//

#include <QApplication>
#include <QDesktopWidget>

#include "ModuleImage.hpp"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    Screenshot screenshot;
    screenshot.move(QApplication::desktop()->availableGeometry(&screenshot).topLeft() + QPoint(20, 20));
    screenshot.show();
    return app.exec();
}
