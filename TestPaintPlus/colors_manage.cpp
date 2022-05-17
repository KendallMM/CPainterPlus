#include "whiteboard.h"
#include "ui_whiteboard.h"

void Whiteboard::on_black_clicked()
{
    scene->color = "#000000";
    ui->currentColor->setStyleSheet("background-color: rgb(0, 0, 0)");
}

void Whiteboard::on_l_grey_clicked()
{
    scene->color = "#d3d3d3";
    ui->currentColor->setStyleSheet("background-color: rgb(191, 191, 191)");
}

void Whiteboard::on_blue_clicked()
{
    scene->color = "#0000FF";
    ui->currentColor->setStyleSheet("background-color: rgb(0, 5, 129)");
}

void Whiteboard::on_sea_clicked()
{
    scene->color = "#006994";
    ui->currentColor->setStyleSheet("background-color: rgb(0, 127, 131)");
}

void Whiteboard::on_green_clicked()
{
    scene->color = "#008000";
    ui->currentColor->setStyleSheet("background-color: rgb(0, 124, 0)");
}

void Whiteboard::on_d_green_clicked()
{
    scene->color = "#006400";
    ui->currentColor->setStyleSheet("background-color: rgb(128, 127, 0)");
}

void Whiteboard::on_d_red_clicked()
{
    scene->color = "#8B0000";
    ui->currentColor->setStyleSheet("background-color: rgb(128, 4, 0)");
}

void Whiteboard::on_violet_clicked()
{
    scene->color = "#800080";
    ui->currentColor->setStyleSheet("background-color: rgb(126, 10, 125)");
}

void Whiteboard::on_grey_clicked()
{
    scene->color = "#808080";
    ui->currentColor->setStyleSheet("background-color: rgb(128, 128, 128)");
}

void Whiteboard::on_white_clicked()
{
    scene->color = "#FFFFFF";
    ui->currentColor->setStyleSheet("background-color: rgb(255, 255, 255)");
}

void Whiteboard::on_l_blue_clicked()
{
    scene->color = "#87CEEB";
    ui->currentColor->setStyleSheet("background-color: rgb(0, 7, 243)");
}

void Whiteboard::on_cyan_clicked()
{
    scene->color = "#00FFFF";
    ui->currentColor->setStyleSheet("background-color: rgb(5, 226, 248)");
}

void Whiteboard::on_l_green_clicked()
{
    scene->color = "#90ee90";
    ui->currentColor->setStyleSheet("background-color: rgb(1, 210, 0)");
}

void Whiteboard::on_yellow_clicked()
{
    scene->color = "#FFFF00";
    ui->currentColor->setStyleSheet("background-color: rgb(249, 236, 9)");
}

void Whiteboard::on_red_clicked()
{
    scene->color = "#FF0000";
    ui->currentColor->setStyleSheet("background-color: rgb(239, 11, 0)");
}

void Whiteboard::on_pink_clicked()
{
    scene->color = "#ffc0cb";
    ui->currentColor->setStyleSheet("background-color: rgb(243, 26, 239)");
}
