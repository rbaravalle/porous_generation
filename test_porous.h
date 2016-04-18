#ifndef TEST_POROUS_H
#define TEST_POROUS_H

#include"Porous.hpp"
#include"Volumetric_texture.hpp"


class Test_Porous
{
public:
    Test_Porous(const int xsize, const int ysize, const int zsize,
    const int separation, const int max_it, const int max_particles,
    const float randomness, const float randomness_z) :
    _xsize(xsize), _ysize(ysize), _zsize(zsize),
    _separation(separation), _max_it(max_it), _max_particles(max_particles),
    _randomness(randomness), _randomness_z(randomness_z)
    {}

    const VolumetricTexture& result() const {return _volume;}

signals:

public slots:
    void run();

private:
    porous::Porous * porous;

    int _xsize, _ysize, _zsize;
    int _separation, _max_it, _max_particles;
    float _randomness, _randomness_z;

    VolumetricTexture _volume;
};

#endif // TEST_POROUS_H
