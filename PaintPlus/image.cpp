#include "image.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <math.h>

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

Image::Image(int width, int height)
    :m_width(width), m_height(height), matriz(width, height)
{
}
Image::~Image()
{
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
            Color *a= new Color(1,1,1);
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
    Image copy(0,0);
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
void Image::Read(const char* path){
    std::ifstream f;
    f.open(path, std::ios::in | std::ios::binary);

    if(!f.is_open()){
        std::cout<<"File could not be open\n";
        return;
    }

    const int fileHeaderSize = 14;
    const int informationHeaderSize = 40;

    unsigned char fileHeader[fileHeaderSize];
    f.read(reinterpret_cast<char*>(fileHeader),fileHeaderSize);

    if(fileHeader[0] != 'B' || fileHeader[1] != 'M')
    {
        std::cout<< "The specified path is not a bitmap image"<< std::endl;
        f.close();
        return;
    }

    unsigned char informationHeader[informationHeaderSize];
    f.read(reinterpret_cast<char*>(informationHeader),informationHeaderSize);

    m_width = informationHeader[4] + (informationHeader[5] << 8) + (informationHeader[6] << 16) + (informationHeader[7] << 24);
    m_height = informationHeader[8] + (informationHeader[9] << 8) + (informationHeader[10] << 16) + (informationHeader[11] << 24);

    matriz.resized(m_width,m_height);

    int r = 0;
    int c = 0;
    for (int y = 0; y < m_height; y++)
    {
        for (int x = 0 ; x < m_width ; x++)
        {
            if (c%m_width==0 && c!=0){
                r++;
                c=0;
            }
            unsigned char color[3];
            f.read(reinterpret_cast<char*>(color),3);
            Color *a= new Color(static_cast<float>(color[2])/255.0f,static_cast<float>(color[1])/255.0f,static_cast<float>(color[0])/255.0f);
            matriz.agregarUltimoObj(a,r,c);
            c++;
        }
    }
    f.close();
    std::cout << "File read "<< std::endl;
}
void Image::Export(const char* path) const{
    std::ofstream f;
    f.open(path, std::ios::out | std::ios::binary);
    if (!f.is_open()){
        std::cout<<"File could not be opened\n";
        return;
    }
    unsigned char bmpPad[3]={0,0,0};
    const int paddingAmount=((4-(m_width*3)%4)%4);
    const int fileHeaderSize=14;
    const int informationHeaderSize=40;
    const int fileSize=fileHeaderSize+informationHeaderSize+m_width*m_height*3+paddingAmount*m_height;

    unsigned char fileHeader[fileHeaderSize];
    //File type
    fileHeader[0]='B';
    fileHeader[1]='M';
    //File size
    fileHeader[2]=fileSize;
    fileHeader[3]=fileSize>>8;
    fileHeader[4]=fileSize>>16;
    fileHeader[5]=fileSize>>24;
    // Reserved 1 (not used)
    fileHeader[6]=0;
    fileHeader[7]=0;
    // Reserved 2 (not used)
    fileHeader[8]=0;
    fileHeader[9]=0;
    // Pixel data offset
    fileHeader[10]=informationHeaderSize;
    fileHeader[11]=0;
    fileHeader[12]=0;
    fileHeader[13]=0;
    unsigned char informationHeader[informationHeaderSize];
    // header size
    informationHeader[0]=informationHeaderSize;
    informationHeader[1]=0;
    informationHeader[2]=0;
    informationHeader[3]=0;
    // Image widht
    informationHeader[4]=m_width;
    informationHeader[5]=m_width>>8;
    informationHeader[6]=m_width>>16;
    informationHeader[7]=m_width>>24;
    // Image height
    informationHeader[8]=m_height;
    informationHeader[9]=m_height>>8;
    informationHeader[10]=m_height>>16;
    informationHeader[11]=m_height>>24;
    // Planes
    informationHeader[12]=1;
    informationHeader[13]=0;
    // bits per pixel (rgb)
    informationHeader[14]=24;
    informationHeader[15]=0;
    // Compression (no compression)
    informationHeader[16]=0;
    informationHeader[17]=0;
    informationHeader[18]=0;
    informationHeader[19]=0;
    //Image size (no compression)
    informationHeader[20]=0;
    informationHeader[21]=0;
    informationHeader[22]=0;
    informationHeader[23]=0;
    // x pixels per meter (not specified)
    informationHeader[24]=0;
    informationHeader[25]=0;
    informationHeader[26]=0;
    informationHeader[27]=0;
    // y pixels per meter (not specified)
    informationHeader[28]=0;
    informationHeader[29]=0;
    informationHeader[30]=0;
    informationHeader[31]=0;
    // Total colors (color palette not used)
    informationHeader[32]=0;
    informationHeader[33]=0;
    informationHeader[34]=0;
    informationHeader[35]=0;
    // Important colors(Generally ignored)
    informationHeader[36]=0;
    informationHeader[37]=0;
    informationHeader[38]=0;
    informationHeader[39]=0;

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
