#ifndef RUNGE_KUTTA_H
#define RUNGE_KUTTA_H

#include<vector>

class Runge_Kutta {
public:

    // use only one instance
    static Runge_Kutta& get_instance() {
        static Runge_Kutta theInstance;
        return theInstance;
    }

    Runge_Kutta() {init();}

    Runge_Kutta(const float dT,
                const float x0, const float y0, const float z0,
                const float x1, const float y1, const float z1,
                const float fx, const float fy,
                const float randomness_z) :
        _dT(dT), _x0(x0), _y0(y0), _z0(z0),
        _x1(x1), _y1(y1), _z1(z1), _fx(fx), _fy(fy),
        _randomness_z(randomness_z)
        {init();}

    void compute(const int x, const int y, const int z,
                 const float cx, const float cy,
                 std::vector<float> & res,
                 const bool inv = false) const;

    // Convenient getters
    float dXm1() {return _dXm1; }
    float dYm1() {return _dYm1; }
    float dZm1() {return _dZm1; }
    float x0() {return _x0; }
    float y0() {return _y0; }
    float z0() {return _z0; }
    float randomness_z() {return _randomness_z; }

private:
    void f1(const float v0, const float v1, const float v2,
            std::vector<float> & res) const;

    void init();

private:
    int _xsize, _ysize, _zsize;

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

//} // namespace

#endif // RUNGE_KUTTA_H
