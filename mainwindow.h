#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include"Porous.hpp"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void output_gui(const VolumetricTexture& occ) const;

private:
    Ui::MainWindow *ui;
    porous::Porous *porous_object;

public slots:
    void test_porous();
};

#endif // MAINWINDOW_H
