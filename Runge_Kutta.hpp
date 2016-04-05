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
                 std::vector<float> & res)
{
    res.clear();

    float xp0 = x*(dXm1)+(x0+cx);
    float xp1 = y*(dYm1)+(y0+cy);
    float xp2 = z*(dZm1)+(z0);

    std::vector<float> temp_1, temp_2, temp_3, temp_4;

    f1(xp0,xp1,xp2, temp_1);

    float k10 = temp_1[0];
    float k11 = temp_1[1];
    float k12 = temp_1[2];


    /*k20,k21,k22 = f1(xp0+k10*0.5,xp1+k11*0.5,xp2+k12*0.5, temp_2);
    k30,k31,k32 = f1(xp0+k20*0.5,xp1+k21*0.5,xp2+k22*0.5, temp_3);
    k40,k41,k42 = f1(xp0+k30,xp1+k31,xp2+k32, temp_4);*/

    res.push_back();
}


} // namespace

#endif // RUNGE_KUTTA_H
