#include"Particle.hpp"
#include"Runge_Kutta.hpp"

#include<random>

#include<iostream>

using namespace std;

namespace porous {

void Particle::init()
{
    _randomness = ((double) rand() / (RAND_MAX));

    _size = 0;

    // initial random position
    int x,y,z;

    x = (int) (((double) rand() / (RAND_MAX)) * _occ.xsize());
    y = (int) (((double) rand() / (RAND_MAX)) * _occ.ysize());
    z = (int) (((double) rand() / (RAND_MAX)) * _occ.zsize());

    cout << "Initial position: " << x << ", " << y << ", "
         << z << endl;

    _owner(x,y,z) = _id;

    // mark boundary
    _owner.set_border(id(), sep(), x, y, z);

    add(x,y,z);

}

void Particle::grow()
{
    cout << "Growing particle.." << endl;
    for(int r = 0; r < 2; r++) {
        int len_boundary = _boundary.size();

        int h;
        for(h = 0; h < len_boundary; h++) {
            int nx = _boundary[h][0];
            int ny = _boundary[h][1];
            int nz = _boundary[h][2];

            if(_occ.in_texture(nx, ny, nz) &&
               _occ(nx, ny, nz) == 1 &&
               !(_owner.search_border(id(), sep(), nx, ny, nz))) {
                _owner(nx, ny, nz) = _id;

                add(nx, ny, nz);

                // found!
                break;
            }
        }


        // delete first h elements
        _boundary.erase(_boundary.begin(), _boundary.begin()+h);

    }

    if(_size > _max_size) _alive = false;

    cout << "Size of particle " << _id << " after growing: "
         << _size << endl;
}

void Particle::add(int x, int y, int z)
{
    
    vector<float> runge_k_res;

    /// \todo Use center of mass instead of (0,0)

    _rk.compute(x, y, z, 0, 0, runge_k_res);

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
                if(! (xh == x && yh == y && zh == z) &&
                      _occ.in_texture(xh, yh, zh) &&
                      _occ(xh, yh, zh) == 1) {
                    /// \todo center of mass
                    int cx = 0;
                    int cy = 0;
                    float xt = (xp0 - (xh*(_rk.dXm1()) + (_rk.x0() + cx)));
                    float yt = (xp1 - (yh*(_rk.dYm1()) + (_rk.y0() + cy)));
                    float zt = (xp2 - (zh*(_rk.dZm1()) +  _rk.z0()));

                    float dist = sqrt(xt*xt + yt*yt + zt*zt);

                    if(dist < dist_min) {
                        dist_min = dist;
                        best_x = xh;
                        best_y = yh;
                        best_z = zh;
                    }

                    // randomly add voxels to the boundary
                    // using the particle random parameter
                    if(rand() / (float)RAND_MAX > (1.0 - _randomness)) {
                        vector<int> new_voxel {xh, yh, zh};
                        _boundary.push_back(new_voxel);
                    }
                }
            }
        }
    }

    assert(_occ(x,y,z) == 1);
    _occ(x,y,z) = 0;
    _size++;
    _owner.set_border(id(), sep(), x, y, z);

    vector<int> new_voxel {best_x, best_y, best_z};
    if(_occ.in_texture(best_x, best_y, best_z) &&
       _occ(best_x, best_y, best_z) == 1)
            _boundary.push_back(new_voxel);

    // randomly add voxels in the z-direction
    if(rand() / RAND_MAX > (1.0 - _rk.randomness_z())) {
        int temp = -1;
        if(rand() / RAND_MAX > 0.5)
            temp = 1;

        vector<int> new_voxel {x, y, z + temp};
        if(_occ.in_texture(x, y, z + temp) &&
           _occ(x, y, z + temp) == 1)
           _boundary.push_back(new_voxel);
    }

}

} // namespace
