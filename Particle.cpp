#include"Particle.hpp"
#include"Particle_tools.hpp"
#include"Runge_Kutta.hpp"

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

                add(nx, ny, nz);
                _size++;

                // found!
                break;
            }
        }


        // delete first h elements
        _boundary.erase(_boundary.begin(), _boundary.begin()+h);

    }

    if(_size > _max_size) _alive = false;
}

void Particle::add(int x, int y, int z)
{

    vector<float> runge_k_res;

    /// \todo Use center of mass instead of (0,0)

    Runge_Kutta::runge_kutta(x, y, z, 0, 0, runge_k_res);

    float xp0 = runge_k_res[0];
    float xp1 = runge_k_res[1];
    float xp2 = runge_k_res[2];

    int best_x = std::numeric_limits<int>::max();
    int best_y = std::numeric_limits<int>::max();
    int best_z = std::numeric_limits<int>::max();

    int dist_min = std::numeric_limits<int>::max();

    for(int xh = x - 1; xh <= x + 1; xh++) {
        for(int yh = y - 1; yh <= y + 1; yh++) {
            for(int zh = z - 1; zh <= z + 1; zh++) {
                if(! (xh == x && yh == y && zh == z) ) {
                    /// \todo center of mass
                    int cx = 0;
                    int cy = 0;
                    float xt = (xp0 - (xh*(Runge_Kutta::dXm1) + (Runge_Kutta::x0 + cx)));
                    float yt = (xp1 - (yh*(Runge_Kutta::dYm1) + (Runge_Kutta::y0 + cy)));
                    float zt = (xp2 - (zh*(Runge_Kutta::dZm1) +  Runge_Kutta::z0));

                    float dist = sqrt(xt*xt + yt*yt + zt*zt);

                    if(dist < dist_min) {
                        dist_min = dist;
                        best_x = xh;
                        best_y = yh;
                        best_z = zh;
                    }

                    // randomly add voxels to the boundary
                    // using the particle random parameter
                    if(rand() / RAND_MAX > (1.0 - _randomness)) {
                        vector<int> new_voxel {xh, yh, zh};
                        _boundary.push_back(new_voxel);
                    }
                }
            }
        }
    }

    particle_tools::occ.set_border((*this), x, y, z);

    vector<int> new_voxel {best_x, best_y, best_z};
    _boundary.push_back(new_voxel);

    // randomly add voxels in the z-direction
    if(rand() / RAND_MAX > (1.0 - Runge_Kutta::randomness_z)) {
        int temp = -1;
        if(rand() / RAND_MAX > 0.5)
            temp = 1;

        vector<int> new_voxel {x, y, z + temp};
        _boundary.push_back(new_voxel);
    }
}
