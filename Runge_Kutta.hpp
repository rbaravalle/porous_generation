#ifndef RUNGE_KUTTA_H
#define RUNGE_KUTTA_H

#include<vector>

class Runge_Kutta {
public:

    Runge_Kutta() {}

    Runge_Kutta(const float dT,
                const int xsize, const int ysize, const int zsize,
                const float randomness_z) :
        _dT(dT),
        _xsize(xsize), _ysize(ysize), _zsize(zsize),
        _randomness_z(randomness_z)
        {init();}

    void compute(const int x, const int y, const int z,
                 std::vector<float> & res,
                 const bool inv = false) const;

    // Convenient getters
    const float dXm1()  const {return _dXm1; }
    const float dYm1()  const {return _dYm1; }
    const float dZm1()  const {return _dZm1; }
    const float x0()  const {return _x0; }
    const float y0()  const {return _y0; }
    const float z0()  const {return _z0; }
    const float randomness_z()  const {return _randomness_z; }

    const float cx()  const {return _cx; }
    const float cy()  const {return _cy; }

private:
    void f1(const float v0, const float v1, const float v2,
            std::vector<float> & res) const;

    void init();

private:
    int _xsize, _ysize, _zsize;
    int _cx, _cy;

    float _dT;

    float _fx;
    float _fy;

    float _m1x;
    float _m1y;
    float _m1z;

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

    float _dXm1;
    float _dYm1;
    float _dZm1;

    float _randomness_z;
};

#endif // RUNGE_KUTTA_H
