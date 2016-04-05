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
    particle_tools::owner.set_border((*this), x, y, z);

}

void Particle::grow()
{
    for(int r = 0; r < 2; r++) {
        int len_boundary = _boundary.size();

        int h;
        for(h = 0; h < len_boundary; h++) {
            int nx = _boundary[h][0];
            int ny = _boundary[h][1];
            int nz = _boundary[h][2];

            if(particle_tools::occ.in_texture(nx, ny, nz) &&
                    !(particle_tools::occ.search_border((*this),
                                                        nx, ny, nz))) {
                particle_tools::occ(nx, ny, nz) = 0;
                particle_tools::owner(nx, ny, nz) = _id;
                _size++;

                // found!
                break;
            }
        }

        /// \todo update boundary

        // delete first h elements
        _boundary.erase(_boundary.begin(), _boundary.begin()+h);

    }

    if(_size > _max_size) _alive = false;
}

void Particle::add(int x, int y, int z)
{
    /// \todo
}
