#include "image.h"
#include "mainwindow.h"


#include <QApplication>
#include <iostream>

int main(int argc, char *argv[])
{

    Image copy(0,0);
    std::cout<<"carga";
    copy.Read("black.bmp");
    std::cout<<"carga";
    copy.Export("copy.bmp");
}
