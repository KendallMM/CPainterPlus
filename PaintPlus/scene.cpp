#include "scene.h"
#include <QDebug>
#include <iostream>


Scene::Scene(QObject *parent) : QGraphicsScene(parent)
{
    size=1;             //standart parameters
    color= Qt::black;
    type = 0;
    contadorZoom=0;
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
    validarCoord();
    if(type==2){
        drawRect();
    }
    if(type==0){
        int dx=abs(last.x() - prev.x());
        int dy=abs(last.y() - prev.y());
        if (dx > dy){
            //passing argument as 0 to plot(x,y)
            DrawLine(prev.x(), prev.y(), last.x(), last.y(), dx, dy, 0);
        }
        //if slope is greater than or equal to 1
        else{
            //passing argument as 1 to plot (y,x)
            DrawLine(prev.y(), prev.x(), last.y(), last.x(), dy, dx, 1);
        }
    }
}

void Scene::bfs(int n, int m, int x, int y, Color prevC, Color newC)
{
    prevC=bmpCanvas.GetColor(x,y);
    bmpCanvas.bfss(n,m,x,y,prevC,newC);
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
    if(type==1){
        if(size!=1){
        PixelInicial(event);
        }
        pencil(event);
    }
    else if (type == 3)     //bucket
    {
        prev = event->scenePos();
        Color b=bmpCanvas.GetColor(0,0);
        prevC=&b;
        Color a(color.redF(),color.greenF(),color.blueF());
        newC=&a;
        bfs(bmpCanvas.getImageWidth(),bmpCanvas.getImageHeight(),bmpCanvas.getImageHeight()-prev.y(),prev.x(),*prevC,*newC);
        bmpCanvas.Export("Canvas.bmp");
        drawImage();
    }
    else if  (type == 4)    //eraser
    {
    pencil(event);
    }
}
void Scene::DrawLine(int x1, int y1, int x2, int y2, int dx, int dy, int decide) {
    Color a(color.redF(),color.greenF(),color.blueF());
    //pk es el parámetro de toma de decisión inicial
    // Nota: los valores x1&y1,x2&y2, dx&dy se intercambian
    // en caso de ser necesario y así que
    // puede manejar casos donde la pendiente sea mayor o menor a 1.
    int pk = 2 * dy - dx;
    for (int i = 0; i <= dx; i++)
    {
        if(size>1){
            for(int r=0;r<size;r++){
                if (decide == 0){
                    bmpCanvas.SetColor(a,bmpCanvas.getImageHeight()-y1-r,x1);
                }else{
                    bmpCanvas.SetColor(a,bmpCanvas.getImageHeight()-x1,y1-r);
                }
            }
        }else{
            if (decide == 0){
                bmpCanvas.SetColor(a,bmpCanvas.getImageHeight()-y1,x1);
            }else{
                bmpCanvas.SetColor(a,bmpCanvas.getImageHeight()-x1,y1);
            }
        }
        //marcando ya sea para disminuir o incrementar el valor
        //si tenemos que graficar de (0,100) a (100,0)
        x1 < x2 ? x1++ : x1--;
        if (pk < 0)
        {
            // el valor de decisión decidirá trazar
            //ya sea x1 o y1 en la posición de x
            if (decide == 0)
            {
                pk = pk + 2 * dy;
            }
            else
            {
                pk = pk + 2 * dy;
            }
        }
        else
        {
            y1 < y2 ? y1++ : y1--;
            pk = pk + 2 * dy - 2 * dx;
        }
    }
    bmpCanvas.Export("Canvas.bmp");
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

    if (type != 1&&type != 3&&type != 4)
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
        pencil(event);
    }
    else if (type == 2)      //rectangle
    {
        if(dots){
            addRect(prev.x(),prev.y(),
                    event->scenePos().x()-prev.x(),
                    event->scenePos().y()-prev.y(),
                QPen(color,size,Qt::DotLine,Qt::SquareCap));
            update();
        }else{
            addRect(prev.x(),prev.y(),
                    event->scenePos().x()-prev.x(),
                    event->scenePos().y()-prev.y(),
                QPen(color,size,Qt::SolidLine,Qt::SquareCap));
            update();
        }

    }
}

void Scene::drawImage()
{
    tempSize=size;
    size=2;
    tempColor=color;
    for(int x = 0; x<bmpCanvas.getImageWidth();x++){
        prevY=0;
        for(int y = 0; y<bmpCanvas.getImageHeight();y++){
            if(y==bmpCanvas.getImageHeight()-2){
                y++;
            }
            if(y<bmpCanvas.getImageHeight()-1){
                a = bmpCanvas.GetColor(bmpCanvas.getImageWidth()-1-x,prevY).r*255;
                b = bmpCanvas.GetColor(bmpCanvas.getImageWidth()-1-x,y+1).r*255;
                c = bmpCanvas.GetColor(bmpCanvas.getImageWidth()-1-x,prevY).g*255;
                d = bmpCanvas.GetColor(bmpCanvas.getImageWidth()-1-x,y+1).g*255;
                e = bmpCanvas.GetColor(bmpCanvas.getImageWidth()-1-x,prevY).b*255;
                f = bmpCanvas.GetColor(bmpCanvas.getImageWidth()-1-x,y+1).b*255;
                if(a==b&&c==d&&e==f){
                    y++;
                }else{
                    rojoHex=decToHexa(bmpCanvas.GetColor(bmpCanvas.getImageWidth()-1-x,prevY).r*255);
                    verdeHex=decToHexa(bmpCanvas.GetColor(bmpCanvas.getImageWidth()-1-x,prevY).g*255);
                    azulHex=decToHexa(bmpCanvas.GetColor(bmpCanvas.getImageWidth()-1-x,prevY).b*255);
                    colorHex=numeral+rojoHex+verdeHex+azulHex;
                    colorChar = colorHex.c_str();
                    color=colorChar;
                    addLine(prevY,
                            x,
                            y,
                            x,
                            QPen(color,size,Qt::SolidLine,Qt::SquareCap));
                    prevY=y+1;
                }
            }else{
                rojoHex=decToHexa(bmpCanvas.GetColor(bmpCanvas.getImageWidth()-1-x,prevY).r*255);
                verdeHex=decToHexa(bmpCanvas.GetColor(bmpCanvas.getImageWidth()-1-x,prevY).g*255);
                azulHex=decToHexa(bmpCanvas.GetColor(bmpCanvas.getImageWidth()-1-x,prevY).b*255);
                colorHex=numeral+rojoHex+verdeHex+azulHex;
                colorChar = colorHex.c_str();
                color=colorChar;
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
void Scene::pencil(QGraphicsSceneMouseEvent *event)
{
    tempColor=color;
    prev.setX(prev.x()+1-size/2);
    prev.setY(prev.y()-1+size/2);
    path.moveTo(prev);
    path.lineTo(event->scenePos().x()+1-size/2,event->scenePos().y()-1+size/2);
    Color pencilColor(color.redF(),color.greenF(),color.blueF());
    if(type==4){
        pencilColor = Color(1,1,1);
        color = "#FFFFFF";
    }
    if(size>1){
        for(int s=0;s<size;s++){
            for(int r=0;r<size;r++){
                int pintarx=event->scenePos().x();
                int pintary=bmpCanvas.getImageHeight()-event->scenePos().y();
                if(event->scenePos().y()+size>bmpCanvas.getImageHeight()){
                    pintary=size-1;
                }
                if(event->scenePos().y()<=0){
                    pintary=bmpCanvas.getImageHeight()-1;
                }if(event->scenePos().x()>=bmpCanvas.getImageHeight()-1){
                    pintarx=bmpCanvas.getImageHeight()-1;
                }if(event->scenePos().x()<size){
                    pintarx=size-1;
                }
                bmpCanvas.SetColor(pencilColor,pintary-r,pintarx-s);
            }
        }
    }else{
        bmpCanvas.SetColor(pencilColor,bmpCanvas.getImageHeight()-event->scenePos().y(),event->scenePos().x());
    }
    removeItem(items()[0]);
    addPath(path, QPen(color,size,Qt::SolidLine,Qt::SquareCap));
    color=tempColor;
    prev = event->scenePos();
    bmpCanvas.Export("Canvas.bmp");
    update();
}
void Scene::PixelInicial(QGraphicsSceneMouseEvent *event)
{
    int x=event->scenePos().x();
    int y=event->scenePos().y();
    addRect(x,y-1,x-x+1-size,y-y-1+size,
                QPen(color,1,Qt::SolidLine,Qt::FlatCap),QBrush(color));
    update();
    prev = event->scenePos();       //save start point
}
void Scene::validarCoord()
{
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
}
