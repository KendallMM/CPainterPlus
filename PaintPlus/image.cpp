#include "image.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <math.h>
using namespace std;

Color::Color()
    : r(0), g(0), b(0)
{
}
Color::Color(float r, float g, float b)
    : r(r), g(g), b(b)
{
}
Color::~Color()
{
}

Image::Image()
    :m_width(), m_height(), matriz()
{
}
Image::~Image()
{
}
void Image::init(int Width, int Height){
    m_width=Width;
    m_height=Height;
    matriz.InitializeMatrix(Width,Height);
}
int Image::getImageHeight(){
    return m_height;
}
int Image::getImageWidth(){
    return m_width;
}
void Image::grayScale(){
    for(int x=0;x<m_width;x++){
        for(int y=0;y<m_width;y++){
            double red = matriz.Matriz[x][y]->r;
            double green = matriz.Matriz[x][y]->g;
            double blue = matriz.Matriz[x][y]->b;
            double avg = (red + green + blue) / 3;
            tempColor.r=avg;
            tempColor.g=avg;
            tempColor.b=avg;
            SetColor(tempColor,x,y);
        }
    }
}
void Image::negativeColors(){
    for(int x=0;x<m_width;x++){
        for(int y=0;y<m_width;y++){
            double red = matriz.Matriz[x][y]->r*255;
            double green = matriz.Matriz[x][y]->g*255;
            double blue = matriz.Matriz[x][y]->b*255;
            red=(255-red)/255;
            green=(255-green)/255;
            blue=(255-blue)/255;
            tempColor.r=red;
            tempColor.g=green;
            tempColor.b=blue;
            SetColor(tempColor,x,y);
        }
    }
}
void Image::pixelate() {
    //loop through each pixel
    for(int w =0;w<m_width;w+=8){
        for(int h=0;h<m_width;h+=8){

            double avgR = 0;
            double avgG = 0;
            double avgB = 0;

            for(int i = w;i < w + 8;i++)
                for(int j = h;j< h+8;j++){
                    avgR = matriz.Matriz[i][j]->r*255;
                    avgG = matriz.Matriz[i][j]->g*255;
                    avgB = matriz.Matriz[i][j]->b*255;

                }
            avgR = (avgR/255);
            avgG = (avgG/255);
            avgB = (avgB/255);
            tempColor.r=avgR;
            tempColor.g=avgG;
            tempColor.b=avgB;

            for(int i=w;i<w+8;i++)
                for(int j=h;j<h+8;j++)
                    SetColor(tempColor,i,j);
        }
    }
}
Color Image::GetColor(int r, int c) const{
    return *matriz.Matriz[r][c];
}
void Image::SetColor(const Color& color, int r, int c){
    matriz.Matriz[r][c]->r = color.r;
    matriz.Matriz[r][c]->g = color.g;
    matriz.Matriz[r][c]->b = color.b;
}
void Image::create(){
    for (int r = 0; r<m_width;r++){
        for(int c = 0; c<m_height;c++){
            matriz.Matriz[c][r]=a;
        }
    }
}
void Image::print(){
    std::cout<<matriz.Matriz[0][0]->r<<std::endl;
    std::cout<<matriz.Matriz[0][0]->g<<std::endl;
    std::cout<<matriz.Matriz[0][0]->b<<std::endl;
}
void Image::cargar(const char* imagenCargada){
    Image copy;
    copy.Read(imagenCargada);
    matriz.cargar(copy.matriz.Matriz,copy.m_width,copy.m_height);
}
void Image::rotar(bool sentidoHorario){
    int temp = m_width;
    m_width=m_height;
    m_height=temp;
    if(sentidoHorario){
        matriz.rotarDerecha();
    }else{
        matriz.rotarIzquierda();
    }
}
void Image::reflejar(bool reflejoVertical){
    int temp = m_width;
    m_width=m_height;
    m_height=temp;
    if(reflejoVertical){
        matriz.reflejoVertical();
    }else{
        matriz.reflejoHorizontal();
    }
}
void Image::Read(const char* path){
    std::ifstream f;
    f.open(path, std::ios::in | std::ios::binary);
    if(!f.is_open()){
        std::cout<<"No se pudo abrir el archivo\n";
        return;
    }
    unsigned char fileHeader[fileHeaderSize];
    f.read(reinterpret_cast<char*>(fileHeader),fileHeaderSize);
    if(fileHeader[0] != 'B' || fileHeader[1] != 'M')
    {
        std::cout<< "La ruta no corresponde a un archivo bmp"<< std::endl;
        f.close();
        return;
    }
    unsigned char informationHeader[informationHeaderSize];
    f.read(reinterpret_cast<char*>(informationHeader),informationHeaderSize);
    m_width = informationHeader[4] + (informationHeader[5] << 8)
            + (informationHeader[6] << 16) + (informationHeader[7] << 24);
    m_height = informationHeader[8] + (informationHeader[9] << 8)
            + (informationHeader[10] << 16) + (informationHeader[11] << 24);
    matriz.InitializeMatrix(m_width,m_height);
    r = 0;
    c = 0;
    for (int y = 0; y < m_height; y++)
    {
        for (int x = 0 ; x < m_width ; x++)
        {
            if (c%m_width==0 && c!=0){
                r++;
                c=0;
            }
            f.read(reinterpret_cast<char*>(color),3);
            k = new Color(static_cast<float>(color[2])/255.0f,
                    static_cast<float>(color[1])/255.0f,
                    static_cast<float>(color[0])/255.0f);
            matriz.agregarUltimoObj(k,r,c);
            c++;
        }
    }
    f.close();
}
void Image::Export(const char* path) const{
    std::ofstream f;
    f.open(path, std::ios::out | std::ios::binary);
    if (!f.is_open()){
        std::cout<<"No se pudo abrir el archivo\n";
        return;
    }
    unsigned char bmpPad[3]={0,0,0};
    const int paddingAmount=((4-(m_width*3)%4)%4);
    const int fileHeaderSize=14;
    const int informationHeaderSize=40;
    const int fileSize=fileHeaderSize+informationHeaderSize+m_width*m_height*3+paddingAmount*m_height;
    unsigned char fileHeader[fileHeaderSize];
    //Tipo de archivo
    fileHeader[0]='B';
    fileHeader[1]='M';
    //Tamano del archivo
    fileHeader[2]=fileSize;fileHeader[3]=fileSize>>8;fileHeader[4]=fileSize>>16;fileHeader[5]=fileSize>>24;
    // Reservado 1
    fileHeader[6]=0;fileHeader[7]=0;
    // Reservado 2
    fileHeader[8]=0;fileHeader[9]=0;
    // Pixel data offset
    fileHeader[10]=informationHeaderSize;fileHeader[11]=0;fileHeader[12]=0;fileHeader[13]=0;unsigned char informationHeader[informationHeaderSize];
    // Tamano del header
    informationHeader[0]=informationHeaderSize;informationHeader[1]=0;informationHeader[2]=0;informationHeader[3]=0;
    // Ancho de la imagen
    informationHeader[4]=m_width;informationHeader[5]=m_width>>8;informationHeader[6]=m_width>>16;informationHeader[7]=m_width>>24;
    // Alto de la imagen
    informationHeader[8]=m_height;informationHeader[9]=m_height>>8;informationHeader[10]=m_height>>16;informationHeader[11]=m_height>>24;
    // Reservado 3
    informationHeader[12]=1;informationHeader[13]=0;
    // Bits por pixel
    informationHeader[14]=24;informationHeader[15]=0;
    // Compresion (no compresion)
    informationHeader[16]=0;informationHeader[17]=0;informationHeader[18]=0;informationHeader[19]=0;
    // Tamano Imagen
    informationHeader[20]=0;informationHeader[21]=0;informationHeader[22]=0;informationHeader[23]=0;
    // Pixeles por metro en "x"
    informationHeader[24]=0;informationHeader[25]=0;informationHeader[26]=0;informationHeader[27]=0;
    // Pixeles por metro en "y"
    informationHeader[28]=0;informationHeader[29]=0;informationHeader[30]=0;informationHeader[31]=0;
    // Colores totales (No se usa paleta de colores)
    informationHeader[32]=0;informationHeader[33]=0;informationHeader[34]=0;informationHeader[35]=0;
    // Colores importantes (se ignora)
    informationHeader[36]=0;informationHeader[37]=0;informationHeader[38]=0;informationHeader[39]=0;
    f.write(reinterpret_cast<char*>(fileHeader),fileHeaderSize);
    f.write(reinterpret_cast<char*>(informationHeader),informationHeaderSize);
    for (int i=0; i<m_height;i++){
        for (int j=0;j<m_width;j++){
            unsigned char r = static_cast<unsigned char>(GetColor(i,j).r*255.0f);
            unsigned char g = static_cast<unsigned char>(GetColor(i,j).g*255.0f);
            unsigned char b = static_cast<unsigned char>(GetColor(i,j).b*255.0f);

            unsigned char color[]={b,g,r};
            f.write(reinterpret_cast<char*>(color),3);
        }
        f.write(reinterpret_cast<char*>(bmpPad),paddingAmount);
    }
    f.close();
    std::cout<<"File created\n";
}
void Image::bfss(int m, int n, int x, int y, Color prevC,Color newC)
{
    // Visiting array
    int vis[1010][1010];


    // Initialing all as zero
    memset(vis, 0, sizeof(vis));

    // Creating queue for bfs
    queue<pair<int, int> > obj;

    // Pushing pair of {x, y}
    obj.push({ x, y });

    // Marking {x, y} as visited
    vis[x][y] = 1;

    // Untill queue is emppty
    while (obj.empty() != 1)
    {

      // Extrating front pair
      pair<int, int> coord = obj.front();
      int x = coord.first;
      int y = coord.second;
      preColor.r = matriz.Matriz[x][y]->r;
      preColor.g = matriz.Matriz[x][y]->g;
      preColor.b = matriz.Matriz[x][y]->b;

      SetColor(newC,x,y);

      // Poping front pair of queue
      obj.pop();

      // For Upside Pixel or Cell
      if (validCoord(x + 1, y, n, m, prevC, newC)
          && vis[x + 1][y] == 0)
      {
        obj.push({ x + 1, y });
        vis[x + 1][y] = 1;
      }

      // For Downside Pixel or Cell
      if (validCoord(x - 1, y, n, m, prevC, newC)
          && vis[x - 1][y] == 0)
      {
          cout<<"AAAA"<<endl;
        obj.push({ x - 1, y });
        vis[x - 1][y] = 1;
      }

      // For Right side Pixel or Cell
      if (validCoord(x, y + 1, n, m, prevC, newC)
          && vis[x][y + 1] == 0)
      {
        obj.push({ x, y + 1 });
        vis[x][y + 1] = 1;
      }

      // For Left side Pixel or Cell
      if (validCoord(x, y - 1, n, m, prevC, newC)
          && vis[x][y - 1] == 0)
      {
        obj.push({ x, y - 1 });
        vis[x][y - 1] = 1;
      }
    }
}

bool Image::validCoord(int x, int y, int n, int m, Color prevC, Color newC)
{
//isValid
    if(x < 0 || x >= m || y < 0 || y > n-1 || matriz.Matriz[x][y]->r != prevC.r||matriz.Matriz[x][y]->g != prevC.g||matriz.Matriz[x][y]->b != prevC.b
       || (matriz.Matriz[x][y]->r == newC.r&&matriz.Matriz[x][y]->g == newC.g&&matriz.Matriz[x][y]->b == newC.b))
        return 0;
    return 1;
}
