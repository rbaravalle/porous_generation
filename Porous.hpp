#ifndef POROUS_H
#define POROUS_H

#include <iostream>
#include <QObject>

#include"Particle.hpp"
#include"Volumetric_texture.hpp"

using namespace std;

namespace porous {

class Porous// : public QOBJECT
{
    //Q_OBJECT

public:

    Porous(const int xsize, const int ysize, const int zsize,
           const int max_size,
           const float randomness,
           const float randomness_z,
           const int max_particles,
           const int max_it) :
        _xsize(xsize), _ysize(ysize), _zsize(zsize),
        _max_size(max_size),
        _max_it(max_it),
        _max_particles(max_particles),
        _randomness(randomness),
        _randomness_z(randomness_z)
    { _occ.resize(xsize, ysize, zsize, 1);
      _owner.resize(xsize, ysize, zsize, -1);
      _rk = Runge_Kutta(0.1, xsize, ysize, zsize);
    }

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

    int _max_it;
    int _max_particles;

    float _randomness;
    float _randomness_z;


private:
    void init_particles();

};

}




#endif // POROUS_H
