#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include <QApplication>

#include <fstream>
#include <vector>
#include <sstream>

#include "pagerank.h"


#include <QTimer>
#include "qcustomplot.h"

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
    void on_pathButton_clicked();

    void on_calculate_clicked();

    void on_calculateF_clicked();

    void on_calculateE_clicked();

    void on_calculateFE_clicked();

    void on_calculateSA_clicked();

    void on_calculateSD_clicked();

    void on_plot_customContextMenuRequested(const QPoint &pos);

    void realtimeDataSlot();
    void bracketDataSlot();
    void screenShot();
    void allScreenShots();


    void makePlot();
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
