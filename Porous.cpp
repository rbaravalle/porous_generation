#include"Porous.hpp"
#include"Particle.hpp"

namespace porous {

void Porous::init_particles(const int cant_particles)
{
    _particles.clear();

    for(int i = 0; i < cant_particles; i++) {

        porous::Particle p(i, _randomness, true, _max_size, 1,
                           _rk, _occ, _owner);

        p.grow();

        _particles.push_back(p);

    }
}

void Porous::algorithm() {

    for(int i = 0; i < _num_it; i++) {


        bool succeeded = false;
        int id;

        for(int p = 0; p < _particles.size(); p++) {
            bool grow = _particles[p].grow();
            if(grow) {
                id = p;
                succeeded = true;
            }
        }

        if(i%5 == 0) {
            cout << "////// ITERATION " << i << endl;
            cout << endl << endl;

            if(!succeeded) {
                cout << "After " << i << " iterations no particle can progress, finishing..." << endl;
                break;
            }
        }


    }
}

}
