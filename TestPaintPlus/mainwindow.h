#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <qrandom.h>
#include <QPainterPath>
#include <QWidget>
#include <QMouseEvent>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void paintEvent( QPaintEvent * event ) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    /*void setColor(QColor selectedColor);
    void setBrushSize(int selectedSize);*/

private:
    Ui::MainWindow *ui;

    /*QColor color;
    bool pressed = false, lapiz = false, lapicero = false, figura = false, borrador = false, ColorPicker = false, cuadrado = false, triangulo = false;
    int PosX,PosY, LapiceroX0 = 0, LapiceroY0 = 0, LapiceroX1 = 0, LapiceroY1 = 0;
    int canvasHeight, canvasWidth;
    bool iniciarPaint;
    std::vector<QPoint> puntos;*/

    QPoint point;
    QPoint point2;
    bool drawingActive;

};
#endif // MAINWINDOW_H
