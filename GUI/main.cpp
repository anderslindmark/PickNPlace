

#include <QtGui>

#include "MainWindow.h"

using namespace PicknPlaceGui;

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow window;
    window.show();
    return app.exec();
}


