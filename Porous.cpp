#include"Porous.hpp"
#include"Particle.hpp"

namespace porous {

void Porous::init_particles(const int cant_particles)
{
    _particles.clear();

    for(int i = 0; i < cant_particles; i++) {
        cout << "Creating one particle..." << endl << endl;
        porous::Particle p(i, _randomness, true, _max_size, 1,
                           _occ, _owner);

        p.grow();

        _particles.push_back(p);

        cout << endl << endl;
    }
}

}
