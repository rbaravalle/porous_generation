#ifndef VOLUMETRIC_TEXTURE_H
#define VOLUMETRIC_TEXTURE_H

#include<vector>
#include"Pixel.hpp"
#include <assert.h>

class VolumetricTexture {
    public:

        VolumetricTexture() {;}

        VolumetricTexture(int xsize, int ysize, int zsize, int init_val) :
            _xsize(xsize), _ysize(ysize), _zsize(zsize), _init_val(init_val)
        {_data.resize(xsize*ysize*zsize, init_val);}

        void resize(const int xsize, const int ysize, const int zsize, const int init_val)
        {
            _xsize = xsize;
            _ysize = ysize;
            _zsize = zsize;
            _data.resize(xsize*ysize*zsize, init_val);
        }

        /// Overloaded access read
        const int& operator() ( const int i, const int j, const int k) const  {
            int index = i + j * _xsize + k * (_xsize*_ysize);
            assert( index < (int)_data.size());
            return _data[index];
        }

        /// Overloaded access read/write
        int& operator()( const int i, const int j, const int k) {
            int index = i + j * _xsize + k * (_xsize*_ysize);
            assert( index < (int)_data.size());
            return _data[index];
        }


        /// Check Pixel within valid range
        bool in_texture(const int x, const int y, const int z) const {
            return (x >= 0) && (x < (int) _xsize) &&
                   (y >= 0) && (y < (int) _ysize) &&
                   (z >= 0) && (z < (int) _zsize);
        }

        /// Check ownership of other particles
        /// in the boundary of a position
        bool search_border(const int id,
                           const int sep,
                           int x, int y, int z) {

            for(int i = -sep; i <= sep; i++)
                for(int j = -sep; j <= sep; j++)
                    for(int k = -sep; k <= sep; k++) {
                        if(in_texture(x+i, y+j, z+k)) {
                            int value = (*this)(x+i, y+j, z+k);
                            if(value > 0 && value != id)
                                return true;
                        }
                    }

            return false;
        }

        /// Set boundary of particle
        /// retaining ownership on it
        void set_border(const int id,
                        const int sep,
                           int x, int y, int z) {

            for(int i = -sep; i <= sep; i++)
                for(int j = -sep; j <= sep; j++)
                    for(int k = -sep; k <= sep; k++) {
                        if(in_texture(x+i, y+j, z+k)) {
                            (*this)(x+i, y+j, z+k) = id;
                        }
                    }

        }

        int xsize() const {return _xsize;}
        int ysize() const {return _ysize;}
        int zsize() const {return _zsize;}

    private:
        int _xsize, _ysize, _zsize, _init_val;
        std::vector<int> _data;
};


#endif // VOLUMETRIC_TEXTURE_H

