#include "injector.h"

#include <cstdio>

#include <QApplication>
#include <QMainWindow>

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    QMainWindow wnd;
    wnd.show();
    
    return app.exec();
}