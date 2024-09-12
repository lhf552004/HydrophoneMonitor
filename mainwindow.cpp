#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    // Initialize the DataGenerator object
    dataGenerator = new DataGenerator(this);

    // Connect signals from DataGenerator to slots in MainWindow
    connect(dataGenerator, &DataGenerator::newData, this, &MainWindow::on_actionUpdatePlot_triggered);

    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
    if (dataGenerator->isRunning()) {
        dataGenerator->stop();
        dataGenerator->wait();
    }
}


void MainWindow::on_actionOpen_triggered()
{

}


void MainWindow::on_actionSave_triggered()
{

}


void MainWindow::on_actionExit_triggered()
{

}


void MainWindow::on_actionAbout_triggered()
{

}


void MainWindow::on_actionStart_triggered()
{
    dataGenerator->start();  // Start the data generation thread
}


void MainWindow::on_actionPause_triggered()
{
    dataGenerator->stop();  // Stop the data generation thread
}


void MainWindow::on_actionReset_triggered()
{

}


void MainWindow::on_actionLog_Data_triggered()
{

}


void MainWindow::on_actionUpdatePlot_triggered()
{

}

