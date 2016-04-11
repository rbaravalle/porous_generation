#ifndef POROUS_H
#define POROUS_H

#include <iostream>

#include"Particle.hpp"
#include"Volumetric_texture.hpp"

using namespace std;

namespace porous {

class Porous {
public:

    Porous(int xsize, int ysize, int zsize,
           int max_size,
           float randomness,
           const vector<porous::Particle>& particles,
           const VolumetricTexture& occ,
           const VolumetricTexture& owner) :
        _xsize(xsize), _ysize(ysize), _zsize(zsize),
        _max_size(max_size),
        _randomness(randomness),
        _rk(Runge_Kutta::get_instance()),
        _particles(particles),
        _occ(occ), _owner(owner)
    {}

    void init_particles(const int cant_particles);

    const vector<porous::Particle>& particles() { return _particles;}

private:
    vector<porous::Particle> _particles;
    VolumetricTexture _occ;
    VolumetricTexture _owner;
    Runge_Kutta & _rk;

    int _xsize, _ysize, _zsize;
    int _max_size;
    float _randomness;
};

}




#endif // POROUS_H
