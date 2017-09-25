#include "rootviewer.h"
#include "ui_rootviewer.h"

#include <iostream>

#include <QFileDialog>
#include <QLabel>
#include <QString>
#include <QStackedWidget>

#include "rootcanvaswidget.h"
#include "rootfile.h"
#include "ttreemodel.h"

#include <TCanvas.h>

RootViewer::RootViewer(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::RootViewer), root_file(nullptr) {
    ui->setupUi(this);
    ui->splitter->setSizes({200, 600});
    ui->stackedWidget->setEnabled(true);
    ui->stackedWidget->widget(0)->setEnabled(true);

    RootCanvasWidget* root_canvas = new RootCanvasWidget(ui->stackedWidget);
    QLabel*           dir_label   = new QLabel("DIRECTORY", ui->stackedWidget);
    dir_label->setAlignment(Qt::AlignCenter);
    ui->stackedWidget->addWidget(root_canvas);
    ui->stackedWidget->addWidget(dir_label);
    connect(ui->actionOpen, &QAction::triggered, this, &RootViewer::openRootFile);
    connect(ui->actionExit, &QAction::triggered, QApplication::instance(), &QApplication::quit);
    connect(ui->stackedWidget, &QStackedWidget::currentChanged,
            [this](int index) {
                if(index==1) {
                    ui->actionExport_Image->setVisible(true);
                    ui->actionExport_Image->setEnabled(true);
                }
                else {
                    ui->actionExport_Image->setVisible(false);
                }
            });
    connect(ui->actionExport_Image, &QAction::triggered, root_canvas, &RootCanvasWidget::exportImg);
    connect(ui->trees, &QTreeView::activated, this, &RootViewer::itemSelected);
}

RootViewer::~RootViewer() { delete ui; }

void RootViewer::itemSelected(const QModelIndex& index) {
    ui->content->setEnabled(false);
    auto oldModel = static_cast<TTreeModel*>(ui->content->model());
    
    ui->content->setModel(nullptr);
    if(oldModel) {
        delete oldModel;
    }

    if (!index.isValid()) return;

    auto item = static_cast<RootFile::Item*>(index.internalPointer());
    ui->statusBar->showMessage(QString("Loading %1...").arg(item->name));
    using RootType = RootFile::Item::RootType;
    if (item->is_tree) {
        TTreeModel* newModel = new TTreeModel(item->key, ui->content);
        ui->content->setModel(newModel);
        ui->content->setEnabled(true);
        ui->content->resizeColumnsToContents();
        connect(ui->content,&QTableView::activated,
                [this](const QModelIndex& index) {
                    ui->content->resizeRowToContents(index.row());
                });
        
        ui->stackedWidget->setCurrentIndex(0);
    }
    else if (item->is_directory) {
        ui->stackedWidget->setCurrentIndex(2);
    }
    else {
        ((RootCanvasWidget*)(ui->stackedWidget->widget(1)))->drawItem(*item);
        ui->stackedWidget->setCurrentIndex(1);
    }
    ui->statusBar->clearMessage();
}

void RootViewer::openRootFile() {
    QString filename = QFileDialog::getOpenFileName(this, "Open File", "", "ROOT Files (*.root)");
    ui->statusBar->showMessage(QString("Loading ROOT file %1").arg(filename));
    root_file            = new RootFile(filename);
    auto root_file_model = new RootFileModel(root_file, ui->trees);
    ui->splitter->setEnabled(true);
    ui->trees->setModel(root_file_model);
    ui->statusBar->clearMessage();
}

void RootViewer::openRootFileName(QString filename) {
    ui->statusBar->showMessage(QString("Loading ROOT file %1").arg(filename));
    root_file            = new RootFile(filename);
    auto root_file_model = new RootFileModel(root_file, ui->trees);
    ui->splitter->setEnabled(true);
    ui->trees->setModel(root_file_model);
    ui->statusBar->clearMessage();
}
