#include<test_porous.h>
#include<Image.h>

int main(int argc, char **argv)
{
    if(argc < 6)
    {
        cout << "Incorrect number of arguments" << endl;
        cout << "Usage: ./a.out max_iterations max_particles max_size randomness z_randomness" << endl;
        return -1;
    }

    cout << "Arguments: " ;
    for(int i = 0; i < argc; i++)
    {
        cout << atof(argv[i]) << ", ";
    }
    cout << endl;

    Test_Porous test(100, 190, 180, 1,
                     atof(argv[1]), // max iterations
                     atof(argv[2]), // max particles
                     atof(argv[3]), // max size
                     atof(argv[4]), // randomness
                     atof(argv[5]));// z randomness

    test.run();

    output_texture(test.result(),
                   "/home/rodrigo/result/",
                   "porous.tga");

    cout << "Success!" << endl;

    return 0;
}
