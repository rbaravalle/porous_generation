#include "test_porous.h"
#include"Image.h"
#include <sstream>

template < typename T > std::string to_string( const T& n )
{
    std::ostringstream stm ;
    stm << n ;
    return stm.str() ;
}

void output_slice(const VolumetricTexture& occ,
                  const int slice,
                  const string& filename)
{
    TGAImage img(occ.xsize(), occ.ysize());

    //declare a temporary color variable
    Colour c;

    //Loop through image and set all pixels to red
    for(int x=0; x< occ.xsize(); x++)
        for(int y=0; y< occ.ysize(); y++)
        {
            c.r = 255*occ(x, y, slice);
            c.g = 255*occ(x, y, slice);
            c.b = 255*occ(x, y, slice);
            c.a = 255;
            img.setPixel(c,y,x);
        }

    //write the image to disk
    img.WriteImage(filename);

}

void output(const VolumetricTexture& occ,
            const string& path,
            const string& filename)
{
    // create dir if not exist

    cout << "Outputting " << occ.zsize() << " image files: " << path + filename << endl;

    for(int i = 0; i < occ.zsize(); i++)
        output_slice(occ, i,
                     path + filename + to_string(i));
}


void Test_Porous::run()
{

    int max_size = 120; //_xsize * _ysize * _zsize;


    porous::Porous porous(_xsize, _ysize, _zsize,
                  _separation,
                  max_size,
                  _randomness,
                  _randomness_z,
                  _max_particles,
                  _max_it);

    clock_t begin = clock(), end;
    // compute
    porous.algorithm();

    end = clock();

    cout << "Total time: "
         <<   double(end - begin) / CLOCKS_PER_SEC << endl;

    // Save result
    _volume = porous.occ();

    // output results
    output(_volume,
           "/home/rodrigo/result/",
           "porous.tga");

    cout << "Success!" << endl;
}
