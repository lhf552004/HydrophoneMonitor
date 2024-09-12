#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QFile>
#include <QMainWindow>
#include "datagenerator.h"
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionOpen_triggered();

    void on_actionSave_triggered();

    void on_actionExit_triggered();

    void on_actionAbout_triggered();

    void on_actionStart_triggered();

    void on_actionPause_triggered();

    void on_actionReset_triggered();

    void on_actionUpdatePlot_triggered();

    void updatePlot(double spl, double frequency, QString timestamp);

private:
    Ui::MainWindow *ui;
    DataGenerator *dataGenerator;  // Pointer to DataGenerator object
    QCustomPlot *customPlot;
    QFile logFile;
    bool isLogging = false;
};
#endif // MAINWINDOW_H
