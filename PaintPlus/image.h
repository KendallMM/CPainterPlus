#include <vector>
#include "matrix.h"
#include <bits/stdc++.h>

class Image
{
public:
    Image();
    ~Image();
    Color GetColor(int r, int c) const;
    void SetColor(const Color& color, int r, int c);
    void Read(const char* path);
    void Export(const char* path) const;
    void rotar(bool sentidoHorario);
    void reflejar(bool reflejoVertical);
    void create();
    void cargar(const char *imagenCargada);
    void init(int Width, int Height);
    int getImageHeight();
    int getImageWidth();
    bool validCoord(int x, int y, int n, int m, Color prevC, Color newC);
    void bfss(int n, int m, int x, int y, Color prevC, Color newC);
    void grayScale();
    void negativeColors();
    void pixelate();
    void cellShade();
private:
    int findClosest(int n);
    const int fileHeaderSize = 14;
    const int informationHeaderSize = 40;
    unsigned char color[3];
    int r,c;
    int m_width;
    int m_height;
    matrix matriz;
    Color tempColor;
    Color preColor;
    Color *k;
    Color *a = new Color(1,1,1);
};
