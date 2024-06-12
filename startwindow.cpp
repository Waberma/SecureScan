#include "startwindow.h"
#include "ui_startwindow.h"
#include "aboutdevwindow.h"
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QStandardItemModel>
#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>
#include <QIcon>

StartWindow::StartWindow(QWidget *parent)
    : QWidget(parent)/*
    , ui(new Ui::StartWindow)*/
{
    //ui->setupUi(this);
    CreateForm();
}

StartWindow::~StartWindow()
{
    delete ui;
}

void StartWindow::openScanWindow()
{
    if(sender()->objectName() == "Тест")
    {
        QString dirPath = QFileDialog::getExistingDirectory(this, "Выбор директории для сканирования");
        if (!dirPath.isEmpty())
        {
            ScanProgressWindow *scanWindow = new ScanProgressWindow(static_cast<QWidget*>(sender()), dirPath);
            connect(scanWindow, &ScanProgressWindow::pizdabolFinish, this, [this]()
            {
                QStandardItemModel *model = new QStandardItemModel();
                model->setItem(0, new QStandardItem("sVirus.exe"));
                fileNameListView->setModel(model);
                fileNameListView->setVisible(true);
            });
            connect(scanWindow, &ScanProgressWindow::pizdabolRasFinish, this, [this]()
            {
                QMessageBox::information(this, "Сканер вирусов", "Процесс сканирования был прерван. Программа не выполнилась.");
            });
            scanWindow->setModal(true);
            scanWindow->show();
            return;
        }
        else
        {
            QMessageBox::warning(this, "Ошибка", "Каталог выбран некорректно!");
            return;
        }
    }
    ScanProgressWindow *scanWindow = new ScanProgressWindow(static_cast<QWidget*>(sender()));
    connect(scanWindow, &ScanProgressWindow::pizdabolRasFinish, this, [this]()
    {
        QMessageBox::information(this, "Сканер вирусов", "Процесс сканирования был прерван. Программа не выполнилась.");
    });
    scanWindow->setModal(true);
    scanWindow->show();
}

void StartWindow::closeApp()
{
    this->close();
}

void StartWindow::CreateForm()
{
    QIcon winIcon(":/icon/icon");
        this->setWindowIcon(winIcon);
    QGridLayout *mainLayout = new QGridLayout();
    this->setWindowTitle("Сканер безопасности");
    this->setLayout(mainLayout);
    QLabel *headerLabel = new QLabel("Сканер безопасности");
    QPushButton *scanSystemBtn = new QPushButton("Сканирование системы");
    scanSystemBtn->setObjectName("Сканирование");
    connect(scanSystemBtn, &QPushButton::clicked, this, &StartWindow::openScanWindow);

    QPushButton *scanFileBtn = new QPushButton("Сканирование каталога");
    scanFileBtn->setObjectName("Тест");
    connect(scanFileBtn, &QPushButton::clicked, this, &StartWindow::openScanWindow);

    QPushButton *developerInfoBtn = new QPushButton("О создателе");
    connect(developerInfoBtn, &QPushButton::clicked, this, [this]()
    {
        AboutDevWindow *win = new AboutDevWindow();
        win->show();
        this->close();
    });
    developerInfoBtn->setStyleSheet("QPushButton { "
                                    "background: transparent; "
                                    "border: none; "
                                    "color: blue; "
                                    "text-decoration: underline; }"
                                );
    QPushButton *exitBtn = new QPushButton("Выход");
    connect(exitBtn, &QPushButton::clicked, this, &StartWindow::closeApp);
    fileNameListView = new QListView();
    fileNameListView->setVisible(false);

    mainLayout->addWidget(headerLabel, 0,0, 1,2, Qt::AlignCenter);
    mainLayout->addWidget(fileNameListView, 1,0, 1,2);
    mainLayout->addWidget(scanSystemBtn, 2,0, 1,1);
    mainLayout->addWidget(exitBtn, 2,1, 1,1);
    mainLayout->addWidget(scanFileBtn, 3,0, 1,1);
    mainLayout->addWidget(developerInfoBtn, 3,1, 1,1);
}

