#include "rootviewer.h"
#include "ui_rootviewer.h"

RootViewer::RootViewer(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::RootViewer)
{
    ui->setupUi(this);
}

RootViewer::~RootViewer()
{
    delete ui;
}
