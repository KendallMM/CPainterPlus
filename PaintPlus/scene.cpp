#include "scene.h"
#include <QDebug>
#include <iostream>

Scene::Scene(QObject *parent) : QGraphicsScene(parent)
{
    size=0;             //standart parameters
    color= Qt::black;
    type = 0;
}
Scene::~Scene()
{}
void Scene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    undo_items.push(items()[0]);    //saving every item in stack
    redo_emit();
    if (items().size() > 0)
        emit clear_emit();
    path = QPainterPath();  //del old path
    last = event->scenePos();
    if(prev.y()-size<0){
        prev.setY(size);
    }
    if(prev.x()+size>bmpCanvas.getImageWidth()){
        prev.setX(prev.x()-size+1);
    }
    if(last.x()>bmpCanvas.getImageWidth()){
        if(size>1){
            last.setX(bmpCanvas.getImageWidth()-size);
        }else{
            last.setX(bmpCanvas.getImageWidth()-1);
        }
    }
    if(last.y()>bmpCanvas.getImageWidth()){
        last.setY(bmpCanvas.getImageWidth());
    }
    if(last.x()<0){
        last.setX(0);
    }
    if(last.y()<0){
        if(size>1){
            last.setY(size);
        }else{
            last.setY(1);
        }

    }
    if(type==2){
        drawRect();
    }
}
void Scene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    //add ellipse on click
    addEllipse(event->scenePos().x(),
               event->scenePos().y(),
               size,
               size,
               QPen(Qt::NoPen),
               QBrush(color));
    prev = event->scenePos();       //save start point
}
void Scene::drawRect()
{
    Color a(color.redF(),color.greenF(),color.blueF());
    if(last.x()<prev.x()){
        QPointF temporalPoint;
        temporalPoint.setX(prev.x());
        prev.setX(last.x());
        last.setX(temporalPoint.x());
    }
    if(last.y()<prev.y()){
        QPointF temporalPoint;
        temporalPoint.setY(prev.y());
        prev.setY(last.y());
        last.setY(temporalPoint.y());
    }

    if(size>1){
        for(int x=prev.x();x<=last.x()+size-1;x++){
            for(int s=0;s<size;s++){
                bmpCanvas.SetColor(a,bmpCanvas.getImageWidth()-prev.y()+s,x);
                bmpCanvas.SetColor(a,bmpCanvas.getImageWidth()-last.y()+s,x);
            }
            if(dots){
                x+=3;
            }
        }
    }else{
        for(int x=prev.x();x<=last.x();x++){
            bmpCanvas.SetColor(a,bmpCanvas.getImageWidth()-prev.y(),x);
            bmpCanvas.SetColor(a,bmpCanvas.getImageWidth()-last.y(),x);
            if(dots){
                x+=3;
            }
        }

    }

    for(int y=prev.y();y<=last.y();y++){
        if(size>1){
            for(int s=0;s<size;s++){
                bmpCanvas.SetColor(a,bmpCanvas.getImageWidth()-y,prev.x()+s);
                bmpCanvas.SetColor(a,bmpCanvas.getImageWidth()-y,last.x()+s);
            }
        }else{
            bmpCanvas.SetColor(a,bmpCanvas.getImageWidth()-y,prev.x());
            bmpCanvas.SetColor(a,bmpCanvas.getImageWidth()-y,last.x());
        }

        if(dots){
            y+=3;
        }
    }

    bmpCanvas.Export("Canvas.bmp");
}

std::string Scene::decToHexa(int n)
{
    if(n==0){
        return "00";
    }
    // char array to store hexadecimal number
    char hexaDeciNum[100];
    std::string hexa;

    // counter for hexadecimal number array
    int i = 0;
    while (n != 0) {
        // temporary variable to store remainder
        int temp = 0;
        // storing remainder in temp variable.
        temp = n % 16;

        // check if temp < 10
        if (temp < 10) {
            hexaDeciNum[i] = temp + 48;
            i++;
        }
        else {
            hexaDeciNum[i] = temp + 55;
            i++;
        }

        n = n / 16;
    }

    // printing hexadecimal number array in reverse order
    for (int j = i - 1; j >= 0; j--){
        hexa+=hexaDeciNum[j];
    }
    return hexa;
}
void Scene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (type != 1)
        removeItem(items()[0]);     //deleting previous item
                                    //until mouse release
    if (type == 0)          //line
    {
        addLine(prev.x(),
                prev.y(),
                event->scenePos().x(),
                event->scenePos().y(),
                QPen(color,size,Qt::SolidLine,Qt::SquareCap));
        update();
    }
    else if  (type == 1)    //curve
    {
        path.moveTo(prev);
        path.lineTo(event->scenePos().x(),event->scenePos().y());
        qDebug() << "Position in y: " << event->scenePos().y();
        Color a(color.redF(),color.greenF(),color.blueF());
        if(event->scenePos().y()>0 && event->scenePos().y()<bmpCanvas.getImageHeight()&&event->scenePos().x()>0&&event->scenePos().x()<bmpCanvas.getImageWidth()){
            bmpCanvas.SetColor(a,bmpCanvas.getImageHeight()-event->scenePos().y(),event->scenePos().x());
        }
        removeItem(items()[0]);
        addPath(path, QPen(color,size,Qt::SolidLine,Qt::SquareCap));
        prev = event->scenePos();
        bmpCanvas.Export("Canvas.bmp");
        update();
    }
    else if (type == 2)      //rectangle
    {
        addRect(prev.x(),prev.y(),
                event->scenePos().x()-prev.x(),
                event->scenePos().y()-prev.y(),
            QPen(color,size,Qt::SolidLine,Qt::SquareCap));
        update();
    }
    else if (type == 3)     //ellipse
    {
        addEllipse(prev.x(),prev.y(),
            event->scenePos().x()-prev.x(),
            event->scenePos().y()-prev.y(),
            QPen(color,size,Qt::SolidLine,Qt::SquareCap));
        qDebug() << "Position in x: " << event->scenePos().x();
        qDebug() << "Position in y: " << event->scenePos().y();
        update();
    }
    else if  (type == 4)    //eraser
    {
        path.moveTo(prev);
        path.lineTo(event->scenePos().x(),event->scenePos().y());
        qDebug() << "Position in x: " << event->scenePos().x();
        qDebug() << "Position in y: " << event->scenePos().y();
        addPath(path, QPen(Qt::white,size,Qt::SolidLine,Qt::SquareCap));
        prev = event->scenePos();
        update();
    }
}
void Scene::drawImage()
{
    int tempSize=size;
    size=2;
    bmpCanvas.Read("Canvas.bmp");
    QColor tempColor=color;
    int prevY=0;
    for(int x = 0; x<bmpCanvas.getImageWidth();x++){
        prevY=0;
        for(int y = 0; y<bmpCanvas.getImageHeight();y++){
            if(y==bmpCanvas.getImageHeight()-2){
                y++;
            }
            if(y<bmpCanvas.getImageHeight()-1){
                int a = bmpCanvas.GetColor(bmpCanvas.getImageWidth()-1-x,prevY).r*255;
                int b = bmpCanvas.GetColor(bmpCanvas.getImageWidth()-1-x,y+1).r*255;
                int c = bmpCanvas.GetColor(bmpCanvas.getImageWidth()-1-x,prevY).g*255;
                int d = bmpCanvas.GetColor(bmpCanvas.getImageWidth()-1-x,y+1).g*255;
                int e = bmpCanvas.GetColor(bmpCanvas.getImageWidth()-1-x,prevY).b*255;
                int f = bmpCanvas.GetColor(bmpCanvas.getImageWidth()-1-x,y+1).b*255;
                if(a==b&&c==d&&e==f){
                    y++;
                }else{
                    std::cout<<"D";
                    std::string numeral="#";
                    std::string rojoHex=decToHexa(bmpCanvas.GetColor(bmpCanvas.getImageWidth()-1-x,prevY).r*255);
                    std::string verdeHex=decToHexa(bmpCanvas.GetColor(bmpCanvas.getImageWidth()-1-x,prevY).g*255);
                    std::string azulHex=decToHexa(bmpCanvas.GetColor(bmpCanvas.getImageWidth()-1-x,prevY).b*255);
                    std::string colorHex=numeral+rojoHex+verdeHex+azulHex;
                    const char * c = colorHex.c_str();
                    color=c;
                    addLine(prevY,
                            x,
                            y,
                            x,
                            QPen(color,size,Qt::SolidLine,Qt::SquareCap));
                    prevY=y+1;
                }
            }else{
                std::cout<<"E";
                std::string numeral="#";
                std::string rojoHex=decToHexa(bmpCanvas.GetColor(bmpCanvas.getImageWidth()-1-x,prevY).r*255);
                std::string verdeHex=decToHexa(bmpCanvas.GetColor(bmpCanvas.getImageWidth()-1-x,prevY).g*255);
                std::string azulHex=decToHexa(bmpCanvas.GetColor(bmpCanvas.getImageWidth()-1-x,prevY).b*255);
                std::string colorHex=numeral+rojoHex+verdeHex+azulHex;
                const char * c = colorHex.c_str();
                color=c;
                addLine(prevY,
                        x,
                        y,
                        x,
                        QPen(color,size,Qt::SolidLine,Qt::SquareCap));
            }
        }
    }
    update();
    color=tempColor;
    size=tempSize;
}



