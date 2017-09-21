#include "rootviewer.h"
#include "ui_rootviewer.h"

#include <QString>
#include <QFileDialog>

#include "rootfile.h"
#include "ttreemodel.h"

RootViewer::RootViewer(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::RootViewer),
    root_file(nullptr)
{
    ui->setupUi(this);
    ui->splitter->setSizes({200, 600});
    connect(ui->actionOpen, &QAction::triggered,
            this, &RootViewer::openRootFile);
    connect(ui->actionExit, &QAction::triggered,
            QApplication::instance(), &QApplication::quit);
    connect(ui->trees, &QTreeView::activated,
            this, &RootViewer::itemSelected);
}

RootViewer::~RootViewer()
{
    delete ui;
}

void RootViewer::itemSelected(const QModelIndex& index)
{
    ui->content->setEnabled(false);
    auto oldModel = ui->content->model();
    ui->content->setModel(nullptr);
    delete oldModel;
    
    if(!index.isValid()) return;
    auto item = static_cast<RootFile::Item*>(index.internalPointer());
    if(!(item->is_tree)) return;
    TTreeModel* newModel = new TTreeModel(item->key, ui->content);
    ui->content->setModel(newModel);
    ui->content->setEnabled(true);
    ui->content->resizeColumnsToContents();
    //ui->content->resizeRowsToContents();
}


void RootViewer::openRootFile()
{
    QString filename = QFileDialog::getOpenFileName(this, "Open File", "", "*.root");
    
    root_file = new RootFile(filename);
    auto root_file_model = new RootFileModel(root_file, ui->trees);
    ui->splitter->setEnabled(true);
    ui->trees->setModel(root_file_model);
}
