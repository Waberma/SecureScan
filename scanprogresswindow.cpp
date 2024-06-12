#include "scanprogresswindow.h"
#include <QGridLayout>
#include <QLabel>
#include <QDebug>
#include <qdir.h>
#include <QMessageBox>
#include <QCloseEvent>
#include <QIcon>

ScanProgressWindow::ScanProgressWindow(QWidget *parent)
{
    CreateForm();
    checkCount = 0;
    fileCount = 500;
    isPizdabol = false;
    qDebug() << "Сканирование";
    StartTimer();
}

void ScanProgressWindow::closeEvent(QCloseEvent* event)
{
    if(!isPizdabol)
    {
        pizdabolRasFinish();
        event->accept();
    }
}

ScanProgressWindow::ScanProgressWindow(QWidget *parent, QString dirPath)
{
    CreateForm();
    qDebug() << "Тестовое сканирование";
    isPizdabol = false;
    checkCount = 0;
    QDir directory(dirPath);
    QStringList files = directory.entryList(QDir::Files | QDir::NoDotAndDotDot);
    fileCount = files.size();
    StartTimer();
    qDebug() << "Количество файлов в каталоге:" << fileCount;
}

void ScanProgressWindow::timerForPizdabolTimeOut()
{
    checkCount++;
    double prog = (double)(checkCount)/fileCount * 100;
    scanProgressBar->setValue(prog);
    int time = rand() % 51 + 10;
    timerForPizdabol->setInterval(time * 100);

    if(checkCount == fileCount)
    {
        scanProgressBar->setValue(100);
        QMessageBox::information(this, "Сканер безопасноти", "Проверка " + QString::number(fileCount) + " файлов завершена!");
        isPizdabol = true;
        pizdabolFinish();
        this->close();
    }
}

void ScanProgressWindow::CreateForm()
{
    QIcon winIcon(":/icon/icon");
        this->setWindowIcon(winIcon);
    this->setFixedSize(225, 70);
    QGridLayout *mainLayout = new QGridLayout();
    this->setWindowTitle("Процесс сканирования...");
    this->setLayout(mainLayout);
    scanProgressBar = new QProgressBar(this);
    scanProgressBar->setFixedWidth(200);
    scanProgressBar->setContentsMargins(15,5,5,5);
    QLabel *headerLabel = new QLabel("Сканирование вирусов...");
    mainLayout->addWidget(headerLabel, 0, 0, Qt::AlignCenter);
    mainLayout->addWidget(scanProgressBar,1, 0, Qt::AlignCenter);
}

void ScanProgressWindow::StartTimer()
{
    timerForPizdabol = new QTimer(this);
    connect(timerForPizdabol, &QTimer::timeout, this, &ScanProgressWindow::timerForPizdabolTimeOut);
    int time = rand() % 51 + 10;
    timerForPizdabol->setInterval(time * 100);
    timerForPizdabol->start();
}

