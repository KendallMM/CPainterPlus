#include "initialwindow.h"
#include "ui_initialwindow.h"



initialWindow::initialWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::initialWindow)
{
    ui->setupUi(this);
}

initialWindow::~initialWindow()
{
    delete ui;
}

void initialWindow::on_pushButton_clicked()
{
    int width = getWidth();
    int height = getHeight();
    if((width == 0 && height == 0)||(width == 0 || height == 0)){
        msgBox.setWindowTitle("Warning");
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setDefaultButton(QMessageBox::Ok);
        msgBox.setEscapeButton(QMessageBox::Ok);
        msgBox.setText("No ha ingresado las dimensiones del canvas");
        msgBox.exec();
    }else{
        Whiteboard *mainWindow = new Whiteboard();
        mainWindow->isModal();
        mainWindow->setCanvasWidth(getWidth());
        mainWindow->setCanvasHeight(getHeight());
        mainWindow->buildCanvas();
        mainWindow->show();
        this->close();
    }

}

int initialWindow::getWidth(){
    return ui->lineancho->text().toInt();
}

int initialWindow::getHeight(){
    return ui->lineancho->text().toInt();
}
