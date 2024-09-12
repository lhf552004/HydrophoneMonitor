#ifndef DATAGENERATOR_H
#define DATAGENERATOR_H
#include <QThread>

class DataGenerator: public QThread
{
    Q_OBJECT
public:
    DataGenerator(QObject *parent = nullptr); // Constructor
    void run() override; // Thread execution starts here
    void stop();
signals:
    void newData(double spl, double frequency, QString timestamp);

private:
    bool running = true;

};

#endif // DATAGENERATOR_H
