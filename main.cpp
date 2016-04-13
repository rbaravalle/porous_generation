#include<iostream>

#include"Porous.hpp"
#include"Image.h"

using namespace std;

void output(const VolumetricTexture& occ,
            const string& filename)
{

    cout << "Outputting image file: " << filename << endl;
    TGAImage img(occ.xsize(), occ.ysize());

    //declare a temporary color variable
    Colour c;

    int z = 0;//zsize/2;
    //Loop through image and set all pixels to red
    for(int x=0; x< occ.xsize(); x++)
        for(int y=0; y< occ.ysize(); y++)
        {
            c.r = 255*occ(x, y, z);
            c.g = 255*occ(x, y, z);
            c.b = 255*occ(x, y, z);
            c.a = 255;
            img.setPixel(c,x,y);
        }

    //write the image to disk
    img.WriteImage(filename);


}

int main()
{
    // init variables
    int xsize = 128;
    int ysize = 128;
    int zsize = 40;
    int max_size = xsize * ysize * zsize;
    float randomness = 0.01;
    int num_particles = 10000;
    int num_it = 1000;

    porous::Porous porous(xsize, ysize, zsize,
                  max_size,
                  randomness,
                  num_particles,
                  num_it);

    // compute
    porous.algorithm();

    // output results
    output(porous.occ(),
           "/home/rodrigo/porous.tga");

    cout << "Success!" << endl;

    return 0;
}

