#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"Porous.hpp"
#include"Image.h"
#include <sstream>


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
    Test_Porous test(
            ui->spinBox_xsize->value(),
            ui->spinBox_ysize->value(),
            ui->spinBox_zsize->value(),
            ui->spinBox_separation->value(),
            ui->spinBox_max_it->value(),
            ui->spinBox_max_particles->value(),
            ui->spinBox_randomness->value(),
            ui->spinBox_randomness_z->value());

    test.run();

    output_gui(test.result());
}

void MainWindow::output_gui(const VolumetricTexture& occ) const
{
    cout << "occ: " << occ.xsize() << endl;
    QImage img(occ.xsize(), occ.ysize(), QImage::Format_Mono);

    int slice = occ.zsize()/2;

    //Loop through image and set all pixels
    for(int x=0; x< occ.xsize(); x++)
        for(int y=0; y< occ.ysize(); y++)
        {
            img.setPixel(x,y,occ(x, y, slice));
        }

    ui->image_label->setPixmap(QPixmap::fromImage(img));
}
