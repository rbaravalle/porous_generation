#include<iostream>

#include"Porous.hpp"

using namespace std;

int main()
{
    int xsize = 30;
    int ysize = 30;
    int zsize = 2;
    int max_size = 10000;
    float randomness = 0.5;
    int num_particles = 40;

    VolumetricTexture occ(xsize, ysize, zsize, 1);
    VolumetricTexture owner(xsize, ysize, zsize, -1);

    porous::Porous porous(xsize, ysize, zsize,
                  max_size,
                  randomness,
                  occ, owner);

    cout << "Creating " << num_particles << " particles..." << endl;

    porous.init_particles(num_particles);

    cout << "Amount of particles created: " << porous.particles().size() << endl;

    cout << "/////////////////// ALGORITHM..." << endl;
    cout << endl << endl;

    int num_it = 1000;

    vector<porous::Particle> & particles = porous.particles();
    for(int i = 0; i < num_it; i++) {
        cout << "////// ITERATION" << endl;
        cout << endl << endl;

        for(int p = 0; p < particles.size(); p++) {
            particles[p].grow();
        }

    }
    cout << "Success!" << endl;


    return 0;
}

