#ifndef INITIALWINDOW_H
#define INITIALWINDOW_H

#include <QWidget>
#include <QMessageBox>
#include "whiteboard.h"

namespace Ui {
class initialWindow;
}

class initialWindow : public QWidget
{
    Q_OBJECT

public:
    explicit initialWindow(QWidget *parent = nullptr);
    ~initialWindow();

private slots:
    void on_pushButton_clicked();

private:
    Ui::initialWindow *ui;
    int getWidth();
    int getHeight();
    QMessageBox msgBox;

};

#endif // INITIALWINDOW_H
