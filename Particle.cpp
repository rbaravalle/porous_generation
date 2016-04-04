#include"Particle.hpp"
#include"Particle_tools.hpp"

#include<random>

using namespace std;

void Particle::init()
{
    vector<int> init_boundary;

    init_boundary.push_back(-1);
    init_boundary.push_back(-1);
    init_boundary.push_back(-1);

    _boundary.push_back(init_boundary);

    _randomness = ((double) rand() / (RAND_MAX));

    _size = 0;


    // initial random position
    int x,y,z;

    x = (int) (((double) rand() / (RAND_MAX)) * particle_tools::occ.xsize());
    y = (int) (((double) rand() / (RAND_MAX)) * particle_tools::occ.ysize());
    z = (int) (((double) rand() / (RAND_MAX)) * particle_tools::occ.zsize());


    particle_tools::occ(x,y,z) = 0;

    particle_tools::owner(x,y,z) = _id;

    // mark boundary

    for(int i = x-1; i <= x+1; i++)
        for(int j = y-1; j <= y+1; j++)
            for(int k = z-1; k <= z+1; k++)
                if(particle_tools::owner.in_texture(x,y,z))
                    particle_tools::owner(i,j,k) = _id;

}

void Particle::grow()
{

}

void Particle::add(int x, int y, int z)
{

}
