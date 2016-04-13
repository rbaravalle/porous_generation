#include<iostream>

#include"Porous.hpp"

using namespace std;

int main()
{
    int xsize = 64;
    int ysize = 64;
    int zsize = 64;
    int max_size = xsize * ysize * zsize;
    float randomness = 0.5;
    int num_particles = 5000;

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

        bool succeeded = false;
        int id;

        for(int p = 0; p < particles.size(); p++) {
            bool grow = particles[p].grow();
            if(grow) {
                id = p;
                succeeded = true;
            }
        }
        if(!succeeded) {
            cout << "After " << i << " iterations no particle can progress, finishing..." << endl;
            break;
        }
        else {
            cout << "Particle " << id << " grew" << endl;
        }

    }
    cout << "Success!" << endl;


    return 0;
}

