#include<iostream>

#include"Porous.hpp"
#include"Image.h"

using namespace std;

int main()
{
    int xsize = 128;
    int ysize = 128;
    int zsize = 40;
    int max_size = xsize * ysize * zsize;
    float randomness = 0.01;
    int num_particles = 10000;
    int num_it = 1000;

    VolumetricTexture occ(xsize, ysize, zsize, 1);
    VolumetricTexture owner(xsize, ysize, zsize, -1);

    porous::Porous porous(xsize, ysize, zsize,
                  max_size,
                  randomness,
                  num_it,
                  occ, owner);

    cout << "Creating " << num_particles << " particles..." << endl;

    porous.init_particles(num_particles);

    cout << "Amount of particles created: " << porous.particles().size() << endl;

    cout << "/////////////////// ALGORITHM..." << endl;
    cout << endl << endl;

    porous.algorithm();

    cout << "Outputting image file" << endl;
    TGAImage img(xsize, ysize);

    //declare a temporary color variable
    Colour c;

    int z = 0;//zsize/2;
    //Loop through image and set all pixels to red
    for(int x=0; x< xsize; x++)
        for(int y=0; y< ysize; y++)
        {
            c.r = 255*occ(x, y, z);
            c.g = 255*occ(x, y, z);
            c.b = 255*occ(x, y, z);
            c.a = 255;
            img.setPixel(c,x,y);
        }

    //write the image to disk
    string filename = "/home/rodrigo/porous.tga";
    img.WriteImage(filename);



    cout << "Success!" << endl;


    return 0;
}

