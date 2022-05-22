#include "whiteboard.h"
#include "ui_whiteboard.h"


Whiteboard::Whiteboard(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Whiteboard),bmpCanvas(0,0)
{
    ui->setupUi(this);

}

Whiteboard::~Whiteboard()
{
    delete ui;
}

void Whiteboard::buildCanvas(){
    scene = new Scene();                //add scene
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setMinimumWidth(getCanvasWidth());
    ui->graphicsView->setMaximumWidth(getCanvasWidth());
    ui->graphicsView->setMinimumHeight(getCanvasHeight());
    ui->graphicsView->setMaximumHeight(getCanvasHeight());
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    timer = new QTimer();
    connect(timer, &QTimer::timeout, this, &Whiteboard::Timer);
    timer->start(100);
    //enable clear after first item add
    //unable redo after item add
    connect(scene, SIGNAL(clear_emit()),this, SLOT(clear_enable()));
    connect(scene, SIGNAL(redo_emit()),this, SLOT(redo_unable()));
    connect(scene, SIGNAL(redo_emit()),this, SLOT(redo_unable()));
    Image temp(getCanvasWidth(),getCanvasHeight());
    bmpCanvas=temp;
    bmpCanvas.create();
    bmpCanvas.Export("Canvas.bmp");
}

//in cpp file
/*void Whiteboard::wheelEvent(QWheelEvent *event){

        ui->graphicsView->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
        // Scale the view / do the zoom
        double scaleFactor = 1.15;
        if(event->angleDelta().y() > 0) {
            // Zoom in
            ui->graphicsView->scale(scaleFactor, scaleFactor);

        } else {
            // Zooming out
             ui->graphicsView->scale(1.0 / scaleFactor, 1.0 / scaleFactor);
        }


        //ui->graphicsView->setTransform(QTransform(h11, h12, h21, h22, 0, 0));
}*/

/*void Whiteboard::wheelEvent(QWheelEvent *event)
{
    if(event->angleDelta().y() > 0)
    {
        if(m_scale < MAX_SCALE)
        {
            std::cout << m_scale << std::endl;
            this->scale(ZOOM_STEP, ZOOM_STEP);
            m_scale *= ZOOM_STEP;
        }
    }
    else if(event->angleDelta().y() < 0)
    {
        if(m_scale >= MIN_SCALE)
        {
            std::cout << m_scale << std::endl;
            this->scale(1/ZOOM_STEP, 1/ZOOM_STEP);
            m_scale *= 1/ZOOM_STEP;
        }
    }
}*/

int Whiteboard::getCanvasHeight(){
    return this->canvasHeight;
}

void Whiteboard::setCanvasWidth(int width){
    this->canvasWidth = width;
}

int Whiteboard::getCanvasWidth(){
    return this->canvasWidth;
}
void Whiteboard::setCanvasHeight(int height){
    this->canvasHeight = height;

}

void Whiteboard::Timer()
{
    timer->stop();
    scene->setSceneRect(0,0, ui->graphicsView->width(), ui->graphicsView->height());
}

void Whiteboard::resizeEvent(QResizeEvent *event)
{
    timer->start(100);
    QWidget::resizeEvent(event);
}

void Whiteboard::on_horizontalSlider_valueChanged(int value)
{
    scene->size = value;
    ui->spinBox->setValue(value);
}

void Whiteboard::on_spinBox_valueChanged(int value)
{
    scene->size = value;
    ui->horizontalSlider->setValue(value);
}

void Whiteboard::on_typeLine_currentIndexChanged(int index)
{
    scene->type = index;
}

void Whiteboard::on_clear_clicked()
{
    scene->clear();                 //undo,redo,clear set unable
    clear_stack("undo");
    clear_stack("redo");
    ui->undo->setEnabled(false);
    ui->redo->setEnabled(false);
    ui->clear->setEnabled(false);
    scene->update();
}

void Whiteboard::clear_enable()
{
    ui->clear->setEnabled(true);
    ui->undo->setEnabled(true);
}

void Whiteboard::redo_unable()
{
    ui->redo->setEnabled(false);
    clear_stack("redo");
}

void Whiteboard::on_undo_clicked()
{
    if (!scene->undo_items.empty())       //just to be sure
    {
        scene->redo_items.push(scene->undo_items.top());
        scene->removeItem(scene->undo_items.top());
        scene->undo_items.pop();
        ui->redo->setEnabled(true);
    }

    if (scene->undo_items.empty())    //set unable if it was last item
        ui->undo->setEnabled(false);
    scene->update();
}

void Whiteboard::on_redo_clicked()
{
    if (!scene->redo_items.empty())       //just to be sure
    {
        scene->addItem(scene->redo_items.top());
        scene->undo_items.push(scene->redo_items.top());
        scene->redo_items.pop();
        ui->undo->setEnabled(true);
    }

    if (scene->redo_items.empty())    //set unable if it was last item
        ui->redo->setEnabled(false);
    scene->update();
}
void Whiteboard::on_Cargar_clicked()
{
    bmpCanvas.Read("Canvas.bmp");
    std::string str = "black.bmp";
    const char * c = str.c_str();
    bmpCanvas.cargar(c);
    bmpCanvas.Export("Canvas.bmp");
}
void Whiteboard::on_rotarD_clicked()
{
    bmpCanvas.Read("Canvas.bmp");
    bmpCanvas.rotar(true);
    bmpCanvas.Export("Canvas.bmp");
}
void Whiteboard::on_rotarI_clicked()
{
    bmpCanvas.Read("Canvas.bmp");
    bmpCanvas.rotar(false);
    bmpCanvas.Export("Canvas.bmp");
}

void Whiteboard::clear_stack(string stack){
    if(stack == "undo"){
        while(!scene->undo_items.empty()){
            scene->undo_items.pop();
        }

    }else{
        while(!scene->redo_items.empty()){
            scene->redo_items.pop();
        }
    }

}

void Whiteboard::on_zoomButton_clicked()
{
    double scaleFactor = 1.15;

    ui->graphicsView->scale(scaleFactor, scaleFactor);

}


void Whiteboard::on_zoomoutButton_clicked()
{
    double scaleFactor = 1.15;

    ui->graphicsView->scale(1.0 / scaleFactor, 1.0 / scaleFactor);

}

