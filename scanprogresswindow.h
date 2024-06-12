#ifndef SCANPROGRESSWINDOW_H
#define SCANPROGRESSWINDOW_H

#include <QWidget>
#include <QDialog>
#include <QProgressBar>
#include <QTimer>
class ScanProgressWindow : public QDialog
{
    Q_OBJECT
signals:
    void pizdabolFinish();
    void pizdabolRasFinish();
public:
    ScanProgressWindow(QWidget *parent);
    ScanProgressWindow(QWidget *parent, QString dirPath);
public slots:
    void closeEvent(QCloseEvent *event);
private slots:
    void timerForPizdabolTimeOut();
private:
    QProgressBar *scanProgressBar;
    QTimer *timerForPizdabol;
    void CreateForm();
    void StartTimer();
    int fileCount;
    int checkCount;
};

#endif // SCANPROGRESSWINDOW_H
