#ifndef PARTICLE_H
#define PARTICLE_H

//#include"Pixel.hpp"
#include<vector>

class Particle {

    public:

        /// Constructor

        Particle(int id, int rand, bool alive, int max_size, int sep) :
            _id(id), _randomness(rand), _alive(alive),
            _max_size(max_size), _sep(sep)
        {
            init();
        }

        /// Destructor

        ~Particle() {}



        /// Try to add (x,y,z) to the occupied set of the particle

        void add(int x, int y, int z);

        /// Grow Particle one step in the simulation

        void grow();

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

        /// Methods

        void init();

};

#endif // PARTICLE_H
