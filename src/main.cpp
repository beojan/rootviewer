#include "rootviewer.h"

#include <TApplication.h>
#include <QApplication>

int main(int argc, char* argv[]) {
    QString filename;
    if (argc == 2) filename = argv[1];
    TApplication rootApp("rootViewer", &argc, argv);
    QApplication app(argc, argv);
    RootViewer   w;
    if (!filename.isEmpty()) w.openRootFileName(filename);
    w.show();

    return app.exec();
}
