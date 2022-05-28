#ifndef WHITEBOARD_H
#define WHITEBOARD_H

#include <QWidget>
#include <QTimer>
#include <QResizeEvent>
#include <QPalette>
#include "scene.h"
#include <QWheelEvent>
#include <QScrollBar>


namespace Ui {
class Whiteboard;
}

class Whiteboard : public QWidget
{
    Q_OBJECT

public:
    explicit Whiteboard(QWidget *parent = nullptr);
    ~Whiteboard();
    int getCanvasWidth();
    void setCanvasWidth(int width);
    int getCanvasHeight();
    void setCanvasHeight(int height);
    void buildCanvas();
    //virtual void wheelEvent(QWheelEvent* event);

private:
    Ui::Whiteboard *ui;
    QTimer *timer;      //timer for scene resize
    Scene *scene;
    int canvasHeight;
    int canvasWidth;

    void resizeEvent(QResizeEvent * event);

private slots:
    void Timer();
    void on_typeLine_currentIndexChanged(int index);
    void on_horizontalSlider_valueChanged(int value);
    void on_spinBox_valueChanged(int value);
    void on_clear_clicked();
    void on_undo_clicked();
    void on_redo_clicked();
    void on_rotarD_clicked();
    void on_rotarI_clicked();
    void on_Cargar_clicked();
    void clear_enable();
    void redo_unable();
    void clear_stack(string stack);

    //colors managment can be implemented
    //with QPalette
    void on_black_clicked();
    void on_l_grey_clicked();
    void on_blue_clicked();
    void on_sea_clicked();
    void on_green_clicked();
    void on_d_green_clicked();
    void on_d_red_clicked();
    void on_violet_clicked();
    void on_grey_clicked();
    void on_white_clicked();
    void on_l_blue_clicked();
    void on_cyan_clicked();
    void on_l_green_clicked();
    void on_yellow_clicked();
    void on_red_clicked();
    void on_pink_clicked();
    void on_zoomButton_clicked();
    void on_zoomoutButton_clicked();
    void on_reflejoVertical_clicked();
    void on_reflejoHorizontal_clicked();
    void on_checkBox_stateChanged();
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_7_clicked();
    void on_pushButton_8_clicked();
};

#endif // WHITEBOARD_H
