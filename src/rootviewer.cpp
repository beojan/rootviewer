#include "rootviewer.h"
#include "ui_rootviewer.h"

#include <iostream>

#include <QFileDialog>
#include <QLabel>
#include <QString>

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
    connect(ui->trees, &QTreeView::activated, this, &RootViewer::itemSelected);
}

RootViewer::~RootViewer() { delete ui; }

void RootViewer::itemSelected(const QModelIndex& index) {
    ui->content->setEnabled(false);
    auto oldModel = ui->content->model();
    ui->content->setModel(nullptr);
    delete oldModel;

    if (!index.isValid()) return;
    auto item = static_cast<RootFile::Item*>(index.internalPointer());

    using RootType = RootFile::Item::RootType;
    if (item->is_tree) {
        TTreeModel* newModel = new TTreeModel(item->key, ui->content);
        ui->content->setModel(newModel);
        ui->content->setEnabled(true);
        ui->content->resizeColumnsToContents();
        ui->stackedWidget->setCurrentIndex(0);
    }
    else if (item->is_directory) {
        ui->stackedWidget->setCurrentIndex(2);
    }
    else if (item->type != RootType::OTHER) {
        ((RootCanvasWidget*)(ui->stackedWidget->widget(1)))->drawItem(*item);
        ui->stackedWidget->setCurrentIndex(1);
    }
}

void RootViewer::openRootFile() {
    QString filename = QFileDialog::getOpenFileName(this, "Open File", "", "*.root");

    root_file            = new RootFile(filename);
    auto root_file_model = new RootFileModel(root_file, ui->trees);
    ui->splitter->setEnabled(true);
    ui->trees->setModel(root_file_model);
}

void RootViewer::openRootFileName(QString filename) {
    root_file            = new RootFile(filename);
    auto root_file_model = new RootFileModel(root_file, ui->trees);
    ui->splitter->setEnabled(true);
    ui->trees->setModel(root_file_model);
}
