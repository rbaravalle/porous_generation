#!/bin/sh
g++ -std=c++11 -I. run_porous.cpp Particle.cpp Runge_Kutta.cpp Porous.cpp Volumetric_texture.cpp Pixel.cpp Image.cpp test_porous.cpp -o porous_generate

