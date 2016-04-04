#ifndef PIXEL_H
#define PIXEL_H

class Pixel {
    public:

        Pixel() : _x(0), _y(0) {}
        Pixel(int x, int y) : _x(x), _y(y) {}

        ~Pixel();

    private:
        int _x;
        int _y;
};

#endif // PIXEL_H
