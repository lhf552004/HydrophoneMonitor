#include "datagenerator.h"
#include <QRandomGenerator>
#include <QDateTime>
#include <iostream>
DataGenerator::DataGenerator(QObject *parent)
    : QThread(parent) {}

void DataGenerator::run() {
    while (running) {
        QThread::sleep(1);  // Generate data every second

        // Generate random floating-point numbers within the range
        double spl = QRandomGenerator::global()->bounded(60.0) + (QRandomGenerator::global()->bounded(60.0));  // Random SPL value in dB from 60.0 to 120.0
        double frequency = QRandomGenerator::global()->bounded(20000.0) + (QRandomGenerator::global()->bounded(20.0));  // Random Frequency in Hz from 20.0 to 20000.0
        QString timestamp = QDateTime::currentDateTime().toString("hh:mm:ss");
        std::cout << "Sending signal of newData" << std::endl;
        emit newData(spl, frequency, timestamp);  // Emit new data signal
    }
}

void DataGenerator::stop() {
    running = false;  // Set running flag to false to stop the thread
}
