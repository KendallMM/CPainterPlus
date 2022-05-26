#include <vector>
#include "matrix.h"

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
    void print();
    void init(int Width, int Height);
    int getImageHeight();
    int getImageWidth();
private:
    int m_width;
    int m_height;
    matrix matriz;
    Color *a = new Color(1,1,1);
};
