#include <iostream>
#include "matrix.h"
using namespace std;

matrix::matrix(int raw, int col){
    tamano=raw*col;
    Matriz = new Color**[tamano];
    raws=raw;
    cols=col;
    for (int i=0; i<tamano; i++){
        Matriz[i]= new Color*[tamano];
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
void matrix::resized(int raw, int col){
    tamano=raw*col;
    Matriz = new Color**[tamano];
    raws=raw;
    cols=col;
    for (int i=0; i<tamano; i++){
        Matriz[i]= new Color*[tamano];
    }
    for (int r = 0; r<raws;r++){
        for(int c = 0; c<cols;c++){
            Matriz[r][c] = NULL;
        }
    }
}

void matrix::rotarIzquierda(){
    Color ***tempMatriz;
    tempMatriz = new Color**[tamano];
    for (int i=0; i<tamano; i++){
        tempMatriz[i]= new Color*[tamano];
    }
    for (int r = 0; r<raws;r++){
        for(int c = 0; c<cols;c++){
            tempMatriz[c][r] = NULL;
        }
    }
    for (int r = 0; r<raws;r++){
        for(int c = 0; c<cols;c++){
            tempMatriz[r][c]=Matriz[cols-1-c][r];
        }
    }
    resized(cols,raws);
    Matriz=tempMatriz;
}
void matrix::rotarDerecha(){
    Color ***tempMatriz;
    tempMatriz = new Color**[tamano];
    for (int i=0; i<tamano; i++){
        tempMatriz[i]= new Color*[tamano];
    }
    for (int r = 0; r<raws;r++){
        for(int c = 0; c<cols;c++){
            tempMatriz[c][r] = NULL;
        }
    }
    for (int r = 0; r<raws;r++){
        for(int c = 0; c<cols;c++){
            tempMatriz[r][c]=Matriz[c][raws-1-r];
        }
    }
    resized(cols,raws);
    Matriz=tempMatriz;
}
void matrix::rotar180(){
    Color ***tempMatriz;
    tempMatriz = new Color**[tamano];
    for (int i=0; i<tamano; i++){
        tempMatriz[i]= new Color*[tamano];
    }
    for (int r = 0; r<raws;r++){
        for(int c = 0; c<cols;c++){
            tempMatriz[c][r] = NULL;
        }
    }
    for (int r = 0; r<raws;r++){
        for(int c = 0; c<cols;c++){
            tempMatriz[c][r]=Matriz[cols-1-c][raws-1-r];
        }
    }
    resized(cols,raws);
    Matriz=tempMatriz;
}
void matrix::invertirHorizontalmente(){
    Color ***tempMatriz;
    tempMatriz = new Color**[tamano];
    for (int i=0; i<tamano; i++){
        tempMatriz[i]= new Color*[tamano];
    }
    for (int r = 0; r<raws;r++){
        for(int c = 0; c<cols;c++){
            tempMatriz[c][r] = NULL;
        }
    }
    for (int r = 0; r<raws;r++){
        for(int c = 0; c<cols;c++){
            tempMatriz[c][raws-1-r]=Matriz[c][r];
        }
    }
    resized(cols,raws);
    Matriz=tempMatriz;
}
void matrix::invertirVerticalmente(){
    Color ***tempMatriz;
    tempMatriz = new Color**[tamano];
    for (int i=0; i<tamano; i++){
        tempMatriz[i]= new Color*[tamano];
    }
    for (int r = 0; r<raws;r++){
        for(int c = 0; c<cols;c++){
            tempMatriz[c][r] = NULL;
        }
    }
    for (int r = 0; r<raws;r++){
        for(int c = 0; c<cols;c++){
            tempMatriz[cols-1-c][r]=Matriz[c][r];
        }
    }
    resized(cols,raws);
    Matriz=tempMatriz;
}
matrix::~matrix(){
    for (int i=0; i<tamano; i++){
        delete Matriz[i];
    }
    delete Matriz;
}
