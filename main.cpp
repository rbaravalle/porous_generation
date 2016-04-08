#include <iostream>

//#include"Particle.hpp"
#include"Particle_tools.hpp"

using namespace std;

int main()
{

    cout << "Creating" << 10 << "particles..." << endl;

    vector<Particle> particles;

    particle_tools::init_particles(10, particles);


    return 0;
}

