#include "image.h"

#include <QApplication>
#include <iostream>

int main()
{

    Image copy(0,0);
    std::cout<<"carga";
    copy.Read("ima.bmp");
    std::cout<<"carga";
    copy.Export("copy.bmp");
}
