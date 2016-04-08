#ifndef GENERATION_DATA_H
#define GENERATION_DATA_H

#include"Particle_tools.hpp"

class Generation_Data {
public:

    // use only one instance
    static Generation_Data& get_instance() {
        static Generation_Data theInstance;
        _g_instance = &theInstance;
        return *_g_instance;
    }

    Generation_data(const int xsize, const int ysize, const int zsize,
                    const int max_size,
                    const int randomness,
                    const std::vector<Particle>& particles) :
        _occ(occ(xsize, ysize, zsize, 1)),
        _owner(owner(xsize, ysize, zsize, -1)), _particles(particles), _randomness(randomness),
        _xsize(xsize), _ysize(ysize), _zsize(zsize) {}

    int randomness() { return _randomness;}
    int max_size() { return _max_size;}


private:
    static Generation_Data* _g_instance;

    // L, L2
    particle_tools::VolumetricTexture _occ, _owner;

    std::vector<Particle> _particles;

    int _randomness;
    int _max_size;
    int _xsize, _ysize, _zsize;
};

#endif // GENERATION_DATA_H
