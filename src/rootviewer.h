#ifndef ROOTVIEWER_H
#define ROOTVIEWER_H

#include <QMainWindow>

namespace Ui {
class RootViewer;
}

class RootViewer : public QMainWindow
{
    Q_OBJECT

public:
    explicit RootViewer(QWidget *parent = 0);
    ~RootViewer();

private:
    Ui::RootViewer *ui;
};

#endif // ROOTVIEWER_H
