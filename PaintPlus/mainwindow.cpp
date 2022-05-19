#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialog_windows.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->newFileButton, SIGNAL(clicked()),this, SLOT(OnNewImage()));

}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::OnNewImage()
{
    QPainter canvasPainter(this);
    canvasPainter.drawPoint(this->x(),this->y());

    CanvasSizeDialog* newCanvas = new CanvasSizeDialog(this, "New Canvas");
    newCanvas->exec();
    // if user hit 'OK' button, create new image
    if (newCanvas->result())
    {
        QSize size = QSize(newCanvas->getWidthValue(),
                           newCanvas->getHeightValue());
        QSize size2 = QSize(newCanvas->getWidthValue()+80,
                           newCanvas->getHeightValue()+80);
        ui->canvas->resize(size);
        this->resize(size2);
    }
    // done with the dialog, free it
    delete newCanvas;
}
void MainWindow::paintEvent()
{
}
