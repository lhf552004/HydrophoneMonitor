#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{


    ui->setupUi(this);

    // Create and set up the QCustomPlot widget
    customPlot = new QCustomPlot(this);
    setCentralWidget(customPlot);  // Set QCustomPlot as the central widget

    // Configure the QCustomPlot
    customPlot->addGraph(); // Add a graph for SPL
    customPlot->graph(0)->setName("SPL (dB)");
    customPlot->graph(0)->setPen(QPen(Qt::blue));  // Set the color for the SPL graph
    customPlot->xAxis->setLabel("Time");
    customPlot->yAxis->setLabel("SPL (dB)");
    customPlot->xAxis->setRange(0, 10);  // Set an initial range for x-axis
    customPlot->yAxis->setRange(60, 120);  // Set an initial range for y-axis (SPL range)

    // Initialize the DataGenerator object
    dataGenerator = new DataGenerator(this);

    // Connect signals from DataGenerator to slots in MainWindow
    connect(dataGenerator, &DataGenerator::newData, this, &MainWindow::updatePlot);

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

void MainWindow::on_actionUpdatePlot_triggered()
{

}

void MainWindow::updatePlot(double spl, double frequency, QString timestamp) {
    // Handle plot update logic here
}
