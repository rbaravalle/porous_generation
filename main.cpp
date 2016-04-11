#include<iostream>

#include"Porous.hpp"

using namespace std;

int main()
{
    int xsize = 255;
    int ysize = 255;
    int zsize = 255;
    int max_size = 10000;
    float randomness = 255;

    vector<porous::Particle> particles;
    VolumetricTexture occ(xsize, ysize, zsize, 1);
    VolumetricTexture owner(xsize, ysize, zsize, -1);

    porous::Porous porous(xsize, ysize, zsize,
                  max_size,
                  randomness,
                  particles,
                  occ, owner);

    cout << "Creating " << 10 << " particles..." << endl;

    porous.init_particles(10);

    cout << "Amount of particles created: " << porous.particles().size() << endl;

    cout << "Success!" << endl;


    return 0;
}

