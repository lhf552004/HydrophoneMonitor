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

    // Configure the QCustomPlot for SPL
    customPlot->addGraph(customPlot->xAxis, customPlot->yAxis); // Add a graph for SPL using the left y-axis
    customPlot->graph(0)->setName("SPL (dB)");
    customPlot->graph(0)->setPen(QPen(Qt::blue));  // Set the color for the SPL graph

    // Configure the QCustomPlot for Frequency
    customPlot->addGraph(customPlot->xAxis, customPlot->yAxis2); // Add a second graph for frequency using the right y-axis
    customPlot->graph(1)->setName("Frequency (Hz)");
    customPlot->graph(1)->setPen(QPen(Qt::red));  // Set the color for the Frequency graph

    // Make the right y-axis visible
    customPlot->yAxis2->setVisible(true);
    customPlot->yAxis->setLabel("SPL (dB)");  // Label for left y-axis
    customPlot->yAxis2->setLabel("Frequency (Hz)");  // Label for right y-axis

    // Configure the x-axis
    customPlot->xAxis->setLabel("Time (s)");
    customPlot->xAxis->setRange(0, 10);  // Set an initial range for x-axis

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
    // Remove all graphs
    customPlot->clearGraphs();

    // Recreate the graph for SPL
    customPlot->addGraph();
    customPlot->graph(0)->setName("SPL (dB)");
    customPlot->graph(0)->setPen(QPen(Qt::blue));  // Set the color for the SPL graph

    // Reset axis labels and ranges
    customPlot->xAxis->setLabel("Time");
    customPlot->yAxis->setLabel("SPL (dB)");
    customPlot->xAxis->setRange(0, 10);  // Reset range for x-axis
    customPlot->yAxis->setRange(60, 120);  // Reset range for y-axis (SPL range)

    // Clear all data (if needed)
    customPlot->graph(0)->data()->clear();

    // Replot to apply changes
    customPlot->replot();

}

void MainWindow::on_actionUpdatePlot_triggered()
{

}

void MainWindow::updatePlot(double spl, double frequency, QString timestamp) {
    // Get the current time in seconds (for x-axis)
    static double startTime = QDateTime::currentDateTime().toMSecsSinceEpoch() / 1000.0;
    double currentTime = QDateTime::currentDateTime().toMSecsSinceEpoch() / 1000.0 - startTime;

    // Add data points to the SPL graph (graph 0)
    customPlot->graph(0)->addData(currentTime, spl);

    // Add data points to the Frequency graph (graph 1)
    customPlot->graph(1)->addData(currentTime, frequency);

    // Rescale axes to make all data visible
    customPlot->graph(0)->rescaleValueAxis();  // Rescale the left y-axis (SPL)
    customPlot->graph(1)->rescaleValueAxis(true);  // Rescale the right y-axis (Frequency)

    // Adjust x-axis range to always show the last 10 seconds of data
    customPlot->xAxis->setRange(currentTime, 10, Qt::AlignRight);

    // Replot to update the graph with the new data
    customPlot->replot();
}

void MainWindow::on_actionLog_triggered()
{
    if (!isLogging) {
        QString filename = QFileDialog::getSaveFileName(this, "Save Log File", "", "*.csv");
        if (!filename.isEmpty()) {
            logFile.setFileName(filename);
            logFile.open(QIODevice::WriteOnly | QIODevice::Text);
            isLogging = true;
        }
    } else {
        logFile.close();
        isLogging = false;
    }
}

