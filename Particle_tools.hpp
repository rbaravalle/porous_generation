#ifndef PARTICLE_TOOLS_H
#define PARTICLE_TOOLS_H

#include<vector>
#include"Pixel.hpp"
#include <assert.h>


namespace particle_tools {

    int xsize = 256;
    int ysize = 256;
    int zsize = 256;

    /// L


    class VolumetricTexture {
        public:
            VolumetricTexture(int xsize, int ysize, int zsize, int init_val) :
                _xsize(xsize), _ysize(ysize), _zsize(zsize), _init_val(init_val)
            {_data.resize(xsize*ysize*zsize, init_val);}

            /// Overloaded access read/write
            int& operator()( const int i, const int j, const int k) {
                int index = i + j * _xsize + k * (_xsize*_ysize);
                assert( index < _data.size());
                return _data[index];
            }


            /// Check Pixel within valid range
            bool in_texture(const int x, const int y, const int z) const {
                return (x >= 0) && (x < (int) _xsize) &&
                       (y >= 0) && (y < (int) _ysize) &&
                       (z >= 0) && (z < (int) _zsize);
            }

            int xsize() const {return _xsize;}
            int ysize() const {return _ysize;}
            int zsize() const {return _zsize;}

        private:
            int _xsize, _ysize, _zsize, _init_val;
            std::vector<int> _data;
    };

    /// L
    VolumetricTexture occ(xsize, ysize, zsize, 1);

    /// L2
    VolumetricTexture owner(xsize, ysize, zsize, -1);



}

#endif // PARTICLE_TOOLS_H

