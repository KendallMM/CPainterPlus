#include <vector>
#include "matrix.h"

class Image
{
public:
    Image(int width, int height);
    ~Image();

    Color GetColor(int r, int c) const;
    void SetColor(const Color& color, int r, int c);
    void Read(const char* path);
    void Export(const char* path) const;
    void rotar(bool sentidoHorario);
private:
    int m_width;
    int m_height;
    matrix matriz;
};
