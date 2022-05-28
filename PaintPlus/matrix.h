#ifndef MATRIX_H
#define MATRIX_H
#include <iostream>



struct Color {
    float r,g,b;
    Color();
    Color(float r, float g, float b);
    ~Color();
};
class matrix
{
int raws,cols;
int tamano;
public:
    matrix();
    void InitializeMatrix(int raw, int col);
    void agregarUltimoObj(Color *, int raw, int col);
    void rotarIzquierda();
    void rotarDerecha();
    void reflejoHorizontal();
    void reflejoVertical();
    void cargar(Color ***matrizCargada, int ancho, int alto);
    void swap(int x1, int x2, int y1, int y2);
    virtual ~matrix();
    Color *a,*b,*c,*d;
    Color* temp;
    Color ***Matriz;

};

#endif // MATRIX_H
