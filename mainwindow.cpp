#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"Porous.hpp"
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
            img.setPixel(c,x,y);
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

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->run_test_button,
            SIGNAL(released()),
            this,
            SLOT(test_porous()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::test_porous() {
    // init variables

    int xsize = ui->spinBox_xsize->value();
    int ysize = ui->spinBox_ysize->value();
    int zsize = ui->spinBox_zsize->value();

    int max_it = ui->spinBox_max_it->value();
    int max_particles = ui->spinBox_max_particles->value();

    float randomness = ui->spinBox_randomness->value();
    float randomness_z = ui->spinBox_randomness_z->value();

    int max_size = xsize * ysize * zsize;


    porous::Porous porous(xsize, ysize, zsize,
                  max_size,
                  randomness,
                  randomness_z,
                  max_particles,
                  max_it);

    clock_t begin = clock(), end;
    // compute
    porous.algorithm();

    end = clock();

    cout << "Total time: "
         <<   double(end - begin) / CLOCKS_PER_SEC << endl;

    // output to Qt GUI
    output_gui(porous.occ());

    // output results
    output(porous.occ(),
           "/home/rodrigo/result/",
           "porous.tga");

    cout << "Success!" << endl;
}

void MainWindow::output_gui(const VolumetricTexture& occ) const
{
    QImage img(occ.xsize(), occ.ysize(), QImage::Format_Mono);

    int slice = 0;

    //Loop through image and set all pixels
    for(int x=0; x< occ.xsize(); x++)
        for(int y=0; y< occ.ysize(); y++)
        {
            img.setPixel(x,y,occ(x, y, slice));
        }

    ui->image_label->setPixmap(QPixmap::fromImage(img));
}
