#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialog_windows.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::OnNewImage()
{
    CanvasSizeDialog* newCanvas = new CanvasSizeDialog(this, "New Canvas");
    newCanvas->exec();
    // if user hit 'OK' button, create new image
    if (newCanvas->result())
    {
        QSize size = QSize(newCanvas->getWidthValue(),
                           newCanvas->getHeightValue());
        drawArea->createNewImage(size);
    }
    // done with the dialog, free it
    delete newCanvas;
}
