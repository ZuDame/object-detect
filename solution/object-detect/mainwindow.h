#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButtonSourceImage_clicked();

    void on_pushButtonSceneImage_clicked();

    void on_pushButtonCpu_clicked();

    void on_pushButtonGpu_clicked();

private:
    Ui::MainWindow *ui;

    // CPU version
    void executeOnCpu();

    // GPU version
    void executeOnGpu();

    // return the number of cuda capable devices
    int checkForCudaCapableDevice();

    // update progressbar value
    //
    // accept an integer value tjat represent the number of recently finished step
    void updateProgressbarValue(int);

    // display updated information on QT
    //
    // data from last kernel (cpu or gpu) is being displayed
    void displayInfo();

    // display exectuion time on QT form
    void displayExecutionTimeCpu();
    void displayExecutionTimeGpu();

    // display general purpose error message as MessageBox
    void displayErrorMsg(QString msg);

    // draw processed image on QT form
    void drawProcessedImage();
};

#endif // MAINWINDOW_H
