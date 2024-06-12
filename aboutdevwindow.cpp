#include "aboutdevwindow.h"
#include "startwindow.h"
#include <QLabel>
#include <QApplication>
#include <QPushButton>
#include <QGridLayout>
#include <QIcon>
AboutDevWindow::AboutDevWindow(QWidget *parent) : QWidget(parent)
{
    CreateForm();
}

void AboutDevWindow::CreateForm()
{

    QIcon winIcon(":/icon/icon");
        this->setWindowIcon(winIcon);
    this->setWindowTitle("О создателе");
    QVBoxLayout *mainLayout = new QVBoxLayout();
    this->setLayout(mainLayout);
    QLabel *header = new QLabel("О создателе");
    header->setAlignment(Qt::AlignCenter);
    QLabel *devFIO = new QLabel("Мастепан Мария Михайловна");
    QLabel *devGrupp = new QLabel("группа ИП-202");
    QLabel *supervisor = new QLabel("Руководитель диплома:");
    QLabel *supervisorFIO = new QLabel("Москаленко Марина Анатольевна");
    QLabel *locationInfo = new QLabel("Ставрополь, 2024");
    QPushButton *exitBtn = new QPushButton("Выход");
    connect(exitBtn, &QPushButton::clicked, this, [this]()
    {
        QApplication::closeAllWindows();
    });
    QPushButton *backBtn = new QPushButton("Назад");
    connect(backBtn, &QPushButton::clicked, this, [this]()
    {
        StartWindow *startWindow = new StartWindow();
        startWindow->show();
        this->close();
    });

    QHBoxLayout *btnLayout = new QHBoxLayout(this);
    btnLayout->addWidget(backBtn);
    btnLayout->addWidget(exitBtn);

    locationInfo->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(header, Qt::AlignCenter);
    mainLayout->addWidget(devFIO);
    mainLayout->addWidget(devGrupp);
    mainLayout->addWidget(supervisor);
    mainLayout->addWidget(supervisorFIO);
    mainLayout->addWidget(locationInfo, Qt::AlignCenter);
    mainLayout->addLayout(btnLayout);

}
