#ifndef ROOTVIEWER_H
#define ROOTVIEWER_H

#include <QMainWindow>
#include <QModelIndex>
class RootFile;
class RootFileModel;

namespace Ui {
class RootViewer;
}

class RootViewer : public QMainWindow
{
    Q_OBJECT

public:
    explicit RootViewer(QWidget *parent = 0);
    ~RootViewer();

public slots:
    void openRootFile();
    void itemSelected(const QModelIndex& index);
    
private:
    Ui::RootViewer *ui;
    RootFile* root_file;
};

#endif // ROOTVIEWER_H
