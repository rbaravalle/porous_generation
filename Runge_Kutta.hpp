#ifndef RUNGE_KUTTA_H
#define RUNGE_KUTTA_H

#include<vector>
#include"Particle_tools.hpp"

namespace Runge_Kutta {

float dT = 0.1;

float fx = 0.1;
float fy = 0.1;


float m1x = 1.0 / particle_tools::xsize;
float m1y = 1.0 / particle_tools::ysize;
float m1z = 1.0 / particle_tools::zsize;

//3D-world limits

float x0 = -3.0*fx;
float x1 = 3.0*fx;
float y0 = -3.0*fy;
float y1 = 3.0*fy;
float z0 = -1;
float z1 = 1;

float diffX = x1-x0;
float diffY = y1-y0;
float diffZ = z1-z0;

float dXm1 = diffX * m1x;
float dYm1 = diffY * m1y;
float dZm1 = diffZ * m1z;

float randomness_z = 0.1;

void f1(const float v0, const float v1, const float v2,
        std::vector<float> & res)
{
    res.clear();
    res.push_back(-v1-0.1*v0*(v0*v0+v1*v1));
    res.push_back(v0-0.1*v1*(v0*v0+v1*v1));
    res.push_back(0);
}

void runge_kutta(const int x, const int y, const int z,
                 const float cx, const float cy,
                 std::vector<float> & res,
                 const bool inv = false)
{
    res.clear();

    float xp0 = x*(dXm1)+(x0+cx);
    float xp1 = y*(dYm1)+(y0+cy);
    float xp2 = z*(dZm1)+(z0);

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

    // inverse
    if(inv) dT *= -1;

    res.push_back(xp0 + dT*(k10 + k20*2.0 + k30*2.0 + k40)*u6);
    res.push_back(xp1 + dT*(k11 + k21*2.0 + k31*2.0 + k41)*u6);
    res.push_back(xp2 + dT*(k12 + k22*2.0 + k32*2.0 + k42)*u6);
}


} // namespace

#endif // RUNGE_KUTTA_H
