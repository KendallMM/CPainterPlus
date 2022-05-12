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
}

void MainWindow::paintEvent( QPaintEvent * event ){
    QPainter painter(this);

    painter.setPen(QPen(Qt::black, 2));

    //ui->pushButton->clearFocus();

    //ui->pushButton->setAutoFillBackground(true);

    //ui->pushButton->setBackgroundRole();

    //ui->pushButton->setForegroundRole();

    //painter.setBackgroundMode();
     QPainterPath path;
    path.moveTo(QRandomGenerator::global()->generate() % 80, QRandomGenerator::global()->generate() % 320);

    path.cubicTo(200, 80, 320, 80, 480, 320);

    painter.setPen(QPen(Qt::black, 8));

    painter.drawPath(path);

}


