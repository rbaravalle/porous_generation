#ifndef RUNGE_KUTTA_H
#define RUNGE_KUTTA_H

#include<vector>

class Runge_Kutta {
public:

    Runge_Kutta() {}

    Runge_Kutta(const float dT,
                const int xsize, const int ysize, const int zsize) :
        _dT(dT),
        _xsize(xsize), _ysize(ysize), _zsize(zsize)
        {init();}

    void compute(const int x, const int y, const int z,
                 std::vector<float> & res,
                 const bool inv = false) const;

    // Convenient getters
    const float xsize_inv()  const {return _xsize_inv; }
    const float ysize_inv()  const {return _ysize_inv; }
    const float zsize_inv()  const {return _zsize_inv; }
    const float x0()  const {return _x0; }
    const float y0()  const {return _y0; }
    const float z0()  const {return _z0; }

    const float cx()  const {return _cx; }
    const float cy()  const {return _cy; }

private:
    void f1(const float v0, const float v1, const float v2,
            float &r1, float &r2, float &r3) const;

    void init();

private:
    int _xsize, _ysize, _zsize;
    int _cx, _cy;

    float _dT;

    float _fx;
    float _fy;

    float _xsize_inv, _ysize_inv, _zsize_inv;

    //3D-world limits

    float _x0;
    float _x1;
    float _y0;
    float _y1;
    float _z0;
    float _z1;

    float _diffX;
    float _diffY;
    float _diffZ;

    float _diffX_px;
    float _diffY_px;
    float _diffZ_px;
};

#endif // RUNGE_KUTTA_H
