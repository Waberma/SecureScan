#ifndef ABOUTDEVWINDOW_H
#define ABOUTDEVWINDOW_H

#include <QWidget>

class AboutDevWindow : public QWidget
{
    Q_OBJECT
public:
    explicit AboutDevWindow(QWidget *parent = nullptr);
private:
    void CreateForm();
signals:

};

#endif // ABOUTDEVWINDOW_H
