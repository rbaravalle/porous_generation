#include"Particle.hpp"
#include"Runge_Kutta.hpp"

#include<random>

#include<iostream>

using namespace std;

namespace porous {

void uneven(const int& xs, int & x) {
    double tmp = (double) rand() / (RAND_MAX);
    if(tmp > 0.5) {
        double tmp2 = (double) rand() / (RAND_MAX);
        if(tmp2 > 0.5) {
            // top
            x = (int) (((double) rand() / (RAND_MAX)) * (xs/4.0));
        }
        else {
            // bottom
            x = (int) (((double) rand() / (RAND_MAX)) * (xs/4.0)) + (3.0*xs/4.0);
        }
    }
    else {
        x = (int) (((double) rand() / (RAND_MAX)) * xs);
    }
}

void generate_random_position(const int& xs,
                              const int& ys,
                              const int& zs,
                              int & x, int & y, int & z)
{

    x = (int) (((double) rand() / (RAND_MAX)) * xs);
    //uneven(xs, x);
    //uneven(ys, y);

    y = (int) (((double) rand() / (RAND_MAX)) * ys);
    z = (int) (((double) rand() / (RAND_MAX)) * zs);
    //uneven(zs, z);
}

void Particle::init()
{
    _size = 0;

    // initial random position
    int x,y,z;

    generate_random_position(_occ.xsize(),
                             _occ.ysize(),
                             _occ.zsize(),
                             x, y, z);

    int count = 0;
    while(_occ(x,y,z) == 0 && count < 5000) {
        generate_random_position(_occ.xsize(),
                                 _occ.ysize(),
                                 _occ.zsize(),
                                 x, y, z);
        count++;
    }

    if(_occ(x,y,z) == 0) {
        _alive = false;
        return;
    }

    //if(y > 0.5*_occ.ysize()) _randomness *= 8.0;
    if(_randomness > 1.0) _randomness = 1.0;

    _owner(x,y,z) = _id;

    // mark boundary
    _owner.set_border(id(), sep(), x, y, z);

    add(x,y,z);

}

bool Particle::grow()
{
    bool succeeded = false;

    for(int r = 0; r < 2 && _alive==true; r++) {
        int len_boundary = _boundary.size();

        int h;
        for(h = 0; h < len_boundary && _alive==true; h++) {
            int nx = _boundary[h][0];
            int ny = _boundary[h][1];
            int nz = _boundary[h][2];

            if(_occ.in_texture(nx, ny, nz) &&
               _occ(nx, ny, nz) == 1 &&
               !(_owner.search_border(id(), sep(), nx, ny, nz))) {
                _owner(nx, ny, nz) = _id;

                add(nx, ny, nz);
                succeeded = true;

                // found!
                break;
            }


            if(_size > _max_size) {
                _alive = false;
            }

        }


        // delete first h elements
        _boundary.erase(_boundary.begin(), _boundary.begin()+h);

    }

    return succeeded;
}

void Particle::add(int x, int y, int z)
{
    srand(time(NULL));
    
    vector<float> runge_k_res (3);

    _rk.compute(x, y, z, runge_k_res);

    float xp0 = runge_k_res[0];
    float xp1 = runge_k_res[1];
    float xp2 = runge_k_res[2];

    int best_x = std::numeric_limits<int>::max();
    int best_y = std::numeric_limits<int>::max();
    int best_z = std::numeric_limits<int>::max();

    float dist_min = std::numeric_limits<float>::max();

    for(int xh = x - 1; xh <= x + 1; xh++) {
        for(int yh = y - 1; yh <= y + 1; yh++) {
            for(int zh = z - 1; zh <= z + 1; zh++) {
                if(! (xh == x && yh == y && zh == z) &&
                      _occ.in_texture(xh, yh, zh) &&
                      _occ(xh, yh, zh) == 1) {

                    /// \todo center of mass
                    // Distance to the result from Runge-kutta
                    float xt = (xp0 - (xh*(_rk.diffX_px()) + (_rk.x0() + _rk.cx())));
                    float yt = (xp1 - (yh*(_rk.diffY_px()) + (_rk.y0() + _rk.cy())));
                    float zt = (xp2 - (zh*(_rk.diffZ_px()) +  _rk.z0()));

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
    if(rand() / RAND_MAX > (1.0 - _randomness_z)) {
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
