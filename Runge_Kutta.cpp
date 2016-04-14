#include"Runge_Kutta.hpp"

#include<iostream>
#include<assert.h>
#include<math.h>

using namespace std;

void Runge_Kutta::f1(const float v0,
                     const float v1,
                     const float v2,
                     float & r1,
                     float & r2,
                     float & r3) const
{
    r1 = v1;
    r2 = -sin(v0);
    r3 = 0;
}

void Runge_Kutta::compute(const int x, const int y, const int z,
         std::vector<float> & res,
         const bool inv) const
{
    res.clear();

    float xp0 = x*(_xsize_inv)+(_x0+_cx);
    float xp1 = y*(_ysize_inv)+(_y0+_cy);
    float xp2 = z*(_zsize_inv)+(_z0);


    float k10, k11, k12, k20, k21, k22, k30, k31, k32,
          k40, k41, k42;

    f1(xp0,xp1,xp2, k10, k11, k12);
    f1(xp0 + k10*0.5, xp1 + k11*0.5, xp2 + k12*0.5,
       k20, k21, k22);

    f1(xp0 + k20*0.5, xp1 + k21*0.5, xp2 + k22*0.5,
       k30, k31, k32);

    f1(xp0+k30, xp1+k31, xp2+k32, k40, k41, k42);

    float u6 = 1.0/6.0;

    float dT = _dT;
    // inverse
    if(inv) dT *= -1;

    res[0] = xp0 + dT*(k10 + k20*2.0 + k30*2.0 + k40)*u6;
    res[1] = xp1 + dT*(k11 + k21*2.0 + k31*2.0 + k41)*u6;
    res[2] = xp2 + dT*(k12 + k22*2.0 + k32*2.0 + k42)*u6;

    /*cout << "Resultado: "
         << xp0 << ", "
         << k10 << ", "
         << k20 << ", "
         << k30 << ", "
         << k40 << ", "
         << endl;*/
}

void Runge_Kutta::init() {

    assert(_xsize > 0);
    _xsize_inv = 1.0 / _xsize;
    _ysize_inv = 1.0 / _ysize;
    _zsize_inv = 1.0 / _zsize;
    _cx = (_xsize / 2.0)*_xsize_inv;
    _cy = (_ysize / 2.0)*_ysize_inv;


    _fx = 1.0;
    _fy = 1.0;
    //3D-world limits
    _x0 = -3.0*_fx;
    _x1 = 3.0*_fx;
    _y0 = -3.0*_fy;
    _y1 = 3.0*_fy;
    _z0 = -1;
    _z1 = 1;

    // diffs in world coordinates
    _diffX = _x1-_x0;
    _diffY = _y1-_y0;
    _diffZ = _z1-_z0;

    // how much in world-coordinates correspond to a pixel
    // example: diff: 6.0 xsize: 128 => diffX_px = 6.0/128
    _diffX_px = _diffX * _xsize_inv;
    _diffY_px = _diffY * _ysize_inv;
    _diffZ_px = _diffZ * _zsize_inv;

}
