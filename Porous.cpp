#include"Porous.hpp"
#include"Particle.hpp"

namespace porous {

void Porous::init_particles()
{
    cout << "Creating " << _cant_particles << " particles..." << endl;

    _particles.clear();

    for(int i = 0; i < _cant_particles; i++) {

        porous::Particle p(i, _randomness, true, _max_size, 1,
                           _rk, _occ, _owner);

        p.grow();

        _particles.push_back(p);

    }
    cout << "Amount of particles created: " << _particles.size() << endl;

}

void Porous::algorithm() {
    init_particles();

    cout << "/////////////////// ALGORITHM..." << endl;
    cout << endl << endl;

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
