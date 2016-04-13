#ifndef PARTICLE_H
#define PARTICLE_H

#include<vector>
#include"Volumetric_texture.hpp"
#include"Runge_Kutta.hpp"

namespace porous {

class Particle {

    public:

        /// Constructor

        Particle(int id, int rand, bool alive, int max_size, int sep,
                 const Runge_Kutta& rk,
                 VolumetricTexture & occ,
                 VolumetricTexture & owner) :
            _id(id), _randomness(rand), _alive(alive),
            _max_size(max_size), _sep(sep), _occ(occ), _owner(owner),
            _rk(rk)
        {
            init();
        }

        /// Destructor

        ~Particle() {}

        ///  Try yo grow the particle one step in the simulation

        bool grow();

        /// Getters
        const int& id() const {return _id;}
        const int& sep() const {return _sep;}

    private:
        int _id;
        int _size;
        float _randomness;
        bool _alive;
        int _max_size;
        int _sep;

        std::vector<std::vector<int>> _boundary;

        /// Instances
        const Runge_Kutta & _rk;
        VolumetricTexture & _occ;
        VolumetricTexture & _owner;

        /// Methods

        void init();

        /// Add (x,y,z) to the occupied set of the particle

        void add(int x, int y, int z);

};

} // namespace porous

#endif // PARTICLE_H
