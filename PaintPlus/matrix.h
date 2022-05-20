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
    matrix(int r, int c);
    void resized(int raw, int col);
    void agregarUltimoObj(Color *, int raw, int col);
    void rotarIzquierda();
    void rotarDerecha();
    void rotar180();
    void invertirHorizontalmente();
    void invertirVerticalmente();
    void cargar(Color ***matrizCargada, int ancho, int alto);
    virtual ~matrix();
    Color ***Matriz;

};

#endif // MATRIX_H
