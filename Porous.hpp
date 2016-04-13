#ifndef POROUS_H
#define POROUS_H

#include <iostream>

#include"Particle.hpp"
#include"Volumetric_texture.hpp"

using namespace std;

namespace porous {

class Porous {
public:

    Porous(const int xsize, const int ysize, const int zsize,
           const int max_size,
           const float randomness,
           const int num_it) :
        _xsize(xsize), _ysize(ysize), _zsize(zsize),
        _max_size(max_size),
        _num_it(num_it),
        _randomness(randomness)
    { _occ.resize(xsize, ysize, zsize, 1);
      _owner.resize(xsize, ysize, zsize, -1);
      _rk = Runge_Kutta(0.1, xsize, ysize, zsize, 0.5);}

    void init_particles(const int cant_particles);

    void algorithm();

    const VolumetricTexture& occ() const {return _occ;}
    const VolumetricTexture& owner() const {return _owner;}


    vector<porous::Particle>& particles() { return _particles;}


private:
    vector<porous::Particle> _particles;
    VolumetricTexture _occ;
    VolumetricTexture _owner;
    Runge_Kutta _rk;

    int _xsize, _ysize, _zsize;
    int _max_size;
    float _randomness;
    int _num_it;
};

}




#endif // POROUS_H
