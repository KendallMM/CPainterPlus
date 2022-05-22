#ifndef SCENE_H
#define SCENE_H


#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QStack>
#include <QPainterPath>
#include <stack>
#include <QWheelEvent>
#include <QTimeLine>

using namespace std;

class Scene : public QGraphicsScene
{

    Q_OBJECT

public:
    int size,type;  //of current object
    QColor color;
    bool drag;
    //QStack<QGraphicsItem*> undo_items, redo_items;
    stack <QGraphicsItem*> undo_items, redo_items;
    //QT undo/redo framework can be used instead
    //of QStack items

    explicit Scene(QObject *parent = 0);
    ~Scene();

private:
    QPainterPath    path;   //path item for curve
    QPointF         prev;   //previous  point

private slots:
    void mousePressEvent(QGraphicsSceneMouseEvent * event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    //void wheelEvent(QGraphicsSceneWheelEvent * event);


signals:
    void clear_emit();
    void redo_emit();
};

#endif // SCENE_H
