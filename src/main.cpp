#include "rootviewer.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    RootViewer w;
    w.show();

    return app.exec();
}

