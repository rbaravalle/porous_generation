#include"Runge_Kutta.hpp"

#include<iostream>

using namespace std;

void Runge_Kutta::f1(const float v0, const float v1, const float v2,
                     std::vector<float> & res) const
{
    res.clear();
    res.push_back(-v1-0.1*v0*(v0*v0+v1*v1));
    res.push_back(v0-0.1*v1*(v0*v0+v1*v1));
    res.push_back(0);
}

void Runge_Kutta::compute(const int x, const int y, const int z,
         const float cx, const float cy,
         std::vector<float> & res,
         const bool inv) const
{
    res.clear();

    float xp0 = x*(_dXm1)+(_x0+cx);
    float xp1 = y*(_dYm1)+(_y0+cy);
    float xp2 = z*(_dZm1)+(_z0);

    std::vector<float> temp_1 (3), temp_2 (3), temp_3 (3), temp_4 (3);

    // using f1

    f1(xp0,xp1,xp2, temp_1);

    float k10 = temp_1[0];
    float k11 = temp_1[1];
    float k12 = temp_1[2];

    f1(xp0 + k10*0.5, xp1 + k11*0.5, xp2 + k12*0.5, temp_2);

    float k20 = temp_2[0];
    float k21 = temp_2[1];
    float k22 = temp_2[2];

    f1(xp0 + k20*0.5, xp1 + k21*0.5, xp2 + k22*0.5, temp_3);

    float k30 = temp_3[0];
    float k31 = temp_3[1];
    float k32 = temp_3[2];

    f1(xp0+k30, xp1+k31, xp2+k32, temp_4);

    float k40 = temp_4[0];
    float k41 = temp_4[1];
    float k42 = temp_4[2];

    float u6 = 1.0/6.0;

    float dT = _dT;
    // inverse
    if(inv) dT *= -1;

    res.push_back(xp0 + dT*(k10 + k20*2.0 + k30*2.0 + k40)*u6);
    res.push_back(xp1 + dT*(k11 + k21*2.0 + k31*2.0 + k41)*u6);
    res.push_back(xp2 + dT*(k12 + k22*2.0 + k32*2.0 + k42)*u6);
}

void Runge_Kutta::init() {

    //3D-world limits

    if(_fx) {
        _x0 = -3.0*_fx;
        _x1 = 3.0*_fx;
        _y0 = -3.0*_fy;
        _y1 = 3.0*_fy;
        _z0 = -1;
        _z1 = 1;
    }
    else {
        _x0 = -3.0;
        _x1 = 3.0;
        _y0 = -3.0;
        _y1 = 3.0;
        _z0 = -1;
        _z1 = 1;

        _dT = 0.1;

        _xsize = 30;
        _ysize = 30;
        _zsize = 1;

        _m1x = 1.0 / _xsize;
        _m1y = 1.0 / _ysize;
        _m1z = 1.0 / _zsize;
    }

    _diffX = _x1-_x0;
    _diffY = _y1-_y0;
    _diffZ = _z1-_z0;

    _dXm1 = _diffX * _m1x;
    _dYm1 = _diffY * _m1y;
    _dZm1 = _diffZ * _m1z;

}
