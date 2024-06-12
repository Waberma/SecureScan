#ifndef STARTWINDOW_H
#define STARTWINDOW_H

#include <QWidget>
#include <QListView>
#include "scanprogresswindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class StartWindow; }
QT_END_NAMESPACE

class StartWindow : public QWidget
{
    Q_OBJECT

public:
    StartWindow(QWidget *parent = nullptr);
    ~StartWindow();
private slots:
    void openScanWindow();
    void closeApp();
private:
    Ui::StartWindow *ui;
    void CreateForm();
    QListView *fileNameListView;
};
#endif // STARTWINDOW_H
