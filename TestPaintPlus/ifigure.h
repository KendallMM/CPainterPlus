#ifndef IFIGURE_H
#define IFIGURE_H
#include "QPoint"
#include <QColor>
#include <QPen>

class IFigure
{
public:
    QPoint start;
    QPoint end;
    QColor lineColor;
    int width;
public:
    IFigure();
    virtual ~IFigure();
    virtual void Draw (QPainter *figuresPainter);


};

#endif // IFIGURE_H
