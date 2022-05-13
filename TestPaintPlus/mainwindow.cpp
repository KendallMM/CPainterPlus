#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;

    drawingActive = false;
}



void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    //When the left mouse button is released, set the flag to false
    if (event->button() == Qt::LeftButton)
    {
        drawingActive = false;
    }
}

void MainWindow::mousePressEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton){

        point=e->pos();

        drawingActive = true;

        update();
    }
}

void MainWindow::paintEvent(QPaintEvent *e)
{
    if(drawingActive){
        setAttribute(Qt::WA_OpaquePaintEvent);
        QPainter painter(this);
        QPen linepen(Qt::red);
        linepen.setCapStyle(Qt::RoundCap);
        linepen.setWidth(30);
        painter.setRenderHint(QPainter::Antialiasing,true);
        painter.setPen(linepen);
        painter.drawPoint(point);
        qDebug() << point;
    }

}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    //Check again if the left mouse button was clicked and whether we are drawing something
    if ((event->buttons() & Qt::LeftButton) && drawingActive)
    {
        point = event->pos();
        qDebug() << point;
        //Update canvas
        this->update();
    }
}
