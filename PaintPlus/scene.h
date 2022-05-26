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
    int size,type;  //of current object
    QColor color;
    bool dots=false;
    //QStack<QGraphicsItem*> undo_items, redo_items;
    stack <QGraphicsItem*> undo_items, redo_items;
    //QT undo/redo framework can be used instead
    //of QStack items
    void drawImage();


    explicit Scene(QObject *parent = 0);
    ~Scene();

private:
    QPainterPath    path;   //path item for curve
    QPointF         last;
    QPointF         prev;   //previous  point


private slots:
    std::string decToHexa(int n);
    void mousePressEvent(QGraphicsSceneMouseEvent * event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    //void wheelEvent(QGraphicsSceneWheelEvent * event);
    void drawRect();


signals:
    void clear_emit();
    void redo_emit();
};

#endif // SCENE_H
