#ifndef SCENE_H
#define SCENE_H


#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QStack>
#include <QPainterPath>
#include <stack>
#include <QWheelEvent>
#include <QTimeLine>
#include "image.h"

using namespace std;

class Scene : public QGraphicsScene
{

    Q_OBJECT

public:
    Image bmpCanvas;
    int type, matrixWidth, tempSize, prevY=0,a,b,c,d,e,f; //of current object
    double contadorZoom, size;
    QColor color, tempColor;
    const char * colorChar;
    bool dots=false;
    std::string numeral="#";
    std::string rojoHex;
    std::string verdeHex;
    std::string azulHex;
    std::string colorHex;
    //QStack<QGraphicsItem*> undo_items, redo_items;
    stack <QGraphicsItem*> undo_items, redo_items;
    //QT undo/redo framework can be used instead
    //of QStack items
    void drawImage();


    explicit Scene(QObject *parent = 0);
    ~Scene();

private:
    Color *newC;
    Color *prevC;
    QPainterPath    path;   //path item for curve
    QPointF         last;
    QPointF         prev;   //previous  point


private slots:
    std::string decToHexa(int n);
    void mousePressEvent(QGraphicsSceneMouseEvent * event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void pencil(QGraphicsSceneMouseEvent *event);
    void PixelInicial(QGraphicsSceneMouseEvent *event);
    void DrawLine(int x1, int y1, int x2, int y2, int dx, int dy, int decide);
    void validarCoordRectangulo();
    void validarCoordLinea();
    //void wheelEvent(QGraphicsSceneWheelEvent * event);
    void bfs(int n, int m, int x, int y,Color prevC, Color newC);
    void drawRect();



signals:
    void clear_emit();
    void redo_emit();
};

#endif // SCENE_H
