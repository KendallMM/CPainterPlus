#include <iostream>
#include "matrix.h"
using namespace std;

matrix::matrix(){
}
void matrix::InitializeMatrix(int raw, int col){
    tamano=raw*col;
    Matriz = new Color**[tamano];
    raws=raw;
    cols=col;
    for (int i=0; i<tamano; i++){
        Matriz[i] = new Color*[tamano];
    }
    for (int r = 0; r<raws;r++){
        for(int c = 0; c<cols;c++){
            Matriz[r][c] = NULL;
        }
    }
}
void matrix::agregarUltimoObj(Color *color, int raw, int col){
    Matriz[raw][col]=color;
}
void matrix::cargar(Color ***MatrizCargada, int ancho, int alto){
    for (int r = 0; r<ancho;r++){
        for(int c = 0; c<alto;c++){
            Matriz[c][r]=MatrizCargada[c][r];
        }
    }
}
void matrix::swap(int x1, int x2, int y1, int y2){
    Color* temp=Matriz[x1][x2];
    Matriz[x1][x2]=Matriz[y1][y2];
    Matriz[y1][y2]=temp;
}
void matrix::resized(int raw, int col){
    raws=raw;
    cols=col;
}
void matrix::rotarIzquierda(){
    int k;
    for (int i = 0; i < raws; i++){
        k = raws-1;
        for (int j = 0; j < k; j++){
        swap(j,i,k,i);
        k--;
        }
    }
    for (int i = 0; i < raws; i++){
        for (int j = i; j < raws; j++){
            swap(i,j,j,i);
        }
    }
    resized(cols,raws);
}
void matrix::rotarDerecha(){
    int n = cols; // n=size of the square matrix
    Color *a,*b,*c,*d;

    // iterate over all the boundaries of the matrix
    for (int i = 0; i <= n / 2 - 1; i++) {

        // for each boundary, keep on taking 4 elements (one
        // each along the 4 edges) and swap them in
        // anticlockwise manner
        for (int j = 0; j <= n - 2 * i - 2; j++) {
            a=Matriz[i + j][i];
            b=Matriz[n - 1 - i][i + j];
            c=Matriz[n - 1 - i - j][n - 1 - i];
            d=Matriz[i][n - 1 - i - j];

            Matriz[i + j][i] = d;
            Matriz[n - 1 - i][i + j] = a;
            Matriz[n - 1 - i - j][n - 1 - i] = b;
            Matriz[i][n - 1 - i - j] = c;
        }
    }
    resized(cols,raws);
}
void matrix::reflejoHorizontal(){
    reflejoVertical();
    rotarIzquierda();
    rotarIzquierda();
    resized(cols,raws);
}
void matrix::reflejoVertical(){
    int k;
    for (int i = 0; i < raws; i++){
        k = raws-1;
        for (int j = 0; j < k; j++){
        swap(j,i,k,i);
        k--;
        }
    }
    resized(cols,raws);
}
matrix::~matrix(){
}
