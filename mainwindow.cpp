#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QDesktopWidget>
#include <QScreen>
#include <QMessageBox>
#include <QMetaEnum>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    MainWindow::makePlot();
}

void MainWindow::makePlot(){
    ui->customPlot->addGraph();
    ui->customPlot->setBackground(QBrush(QColor("#282828")));
    ui->customPlot->graph(0)->setPen(QPen(QColor("#28efa9")));
    ui->customPlot->graph(0)->setBrush(QBrush(QColor(40, 239, 169, 140)));
    ui->customPlot->xAxis2->setLabelColor(QColor("#28efa9"));
    ui->customPlot->yAxis2->setLabelColor(QColor("#28efa9"));
    ui->customPlot->xAxis2->setTickLabelColor(QColor("#28efa9"));
    ui->customPlot->yAxis2->setTickLabelColor(QColor("#28efa9"));
    ui->customPlot->xAxis2->setTickPen(QColor("#28efa9"));
    ui->customPlot->yAxis2->setTickPen(QColor("#28efa9"));
    ui->customPlot->xAxis2->setSubTickPen(QColor("#28efa9"));
    ui->customPlot->yAxis2->setSubTickPen(QColor("#28efa9"));
    ui->customPlot->xAxis2->setBasePen(QColor("#28efa9"));
    ui->customPlot->yAxis2->setBasePen(QColor("#28efa9"));
    ui->customPlot->xAxis2->setSelectedLabelColor(QColor("#28efa9"));
    ui->customPlot->yAxis2->setSelectedLabelColor(QColor("#28efa9"));
    ui->customPlot->xAxis2->setSelectedTickLabelColor(QColor("#28efa9"));
    ui->customPlot->yAxis2->setSelectedTickLabelColor(QColor("#28efa9"));
    ui->customPlot->xAxis2->setSelectedTickPen(QColor("#28efa9"));
    ui->customPlot->yAxis2->setSelectedTickPen(QColor("#28efa9"));
    ui->customPlot->xAxis2->setSelectedSubTickPen(QColor("#28efa9"));
    ui->customPlot->yAxis2->setSelectedSubTickPen(QColor("#28efa9"));
    ui->customPlot->xAxis2->setSelectedBasePen(QColor("#28efa9"));
    ui->customPlot->yAxis2->setSelectedBasePen(QColor("#28efa9"));
    ui->customPlot->xAxis->setLabelColor(QColor("#28efa9"));
    ui->customPlot->yAxis->setLabelColor(QColor("#28efa9"));
    ui->customPlot->xAxis->setTickLabelColor(QColor("#28efa9"));
    ui->customPlot->yAxis->setTickLabelColor(QColor("#28efa9"));
    ui->customPlot->xAxis->setTickPen(QColor("#28efa9"));
    ui->customPlot->yAxis->setTickPen(QColor("#28efa9"));
    ui->customPlot->xAxis->setSubTickPen(QColor("#28efa9"));
    ui->customPlot->yAxis->setSubTickPen(QColor("#28efa9"));
    ui->customPlot->xAxis->setBasePen(QColor("#28efa9"));
    ui->customPlot->yAxis->setBasePen(QColor("#28efa9"));
    ui->customPlot->xAxis->setSelectedLabelColor(QColor("#28efa9"));
    ui->customPlot->yAxis->setSelectedLabelColor(QColor("#28efa9"));
    ui->customPlot->xAxis->setSelectedTickLabelColor(QColor("#28efa9"));
    ui->customPlot->yAxis->setSelectedTickLabelColor(QColor("#28efa9"));
    ui->customPlot->xAxis->setSelectedTickPen(QColor("#28efa9"));
    ui->customPlot->yAxis->setSelectedTickPen(QColor("#28efa9"));
    ui->customPlot->xAxis->setSelectedSubTickPen(QColor("#28efa9"));
    ui->customPlot->yAxis->setSelectedSubTickPen(QColor("#28efa9"));
    ui->customPlot->xAxis->setSelectedBasePen(QColor("#28efa9"));
    ui->customPlot->yAxis->setSelectedBasePen(QColor("#28efa9"));
    // generate some points of data (y0 for first, y1 for second graph):
    // configure right and top axis to show ticks but no labels:
    // (see QCPAxisRect::setupFullAxesBox for a quicker method to do this)
    ui->customPlot->xAxis2->setVisible(true);
    ui->customPlot->xAxis2->setTickLabels(false);
    ui->customPlot->yAxis2->setVisible(true);
    ui->customPlot->yAxis2->setTickLabels(false);
    // make left and bottom axes always transfer their ranges to right and top axes:
    connect(ui->customPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->customPlot->xAxis2, SLOT(setRange(QCPRange)));
    connect(ui->customPlot->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->customPlot->yAxis2, SLOT(setRange(QCPRange)));
    // pass data points to graphs:
    // Note: we could have also just called customPlot->rescaleAxes(); instead
    // Allow user to drag axis ranges with mouse, zoom with mouse wheel and select graphs by clicking:
    ui->customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);

}



MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pathButton_clicked()
{
    QString fileName =
            QFileDialog::getOpenFileName(this, tr("Open json file"), "C:/Users/Christian/Documents/Qt Projects/Projet Methode PageRank Christian Gemayel 161515/PageRankGUI/json",
                                         tr("json files (*.json)"));

    if (!fileName.isEmpty()) {
        ui->pathLabel->setText(fileName);
    }
}

void MainWindow::on_calculate_clicked()
{
    ui->nameText->clear();
    ui->pRankText->clear();
    std::ifstream file(ui->pathLabel->text().toStdString());
    nlohmann::json j;
    file >> j;
    PageRank p;
    p.calculate(j,ui->bText->text().toDouble(),ui->iterationsText->text().toDouble(), ui->customPlot);
    for(int i(0);i<p.getSize();++i){
        QString strAll = QString::fromStdString(p.getAll(i));
        QString strVp = QString::number(p.getVp(i));
        ui->nameText->append(strAll);
        ui->pRankText->append(strVp);
    }


}

void MainWindow::on_calculateF_clicked()
{
    ui->nameText->clear();
    ui->pRankText->clear();
    std::ifstream file(ui->pathLabel->text().toStdString());
    nlohmann::json j;
    file >> j;
    PageRank p;
    p.calculateFaulty(j,ui->iterationsText->text().toDouble(), ui->customPlot);
    for(int i(0);i<p.getSize();++i){
        QString strAll = QString::fromStdString(p.getAll(i));
        QString strVp = QString::number(p.getVp(i));
        ui->nameText->append(strAll);
        ui->pRankText->append(strVp);
}
}

void MainWindow::on_calculateE_clicked()
{
    ui->nameText->clear();
    ui->pRankText->clear();
    std::ifstream file(ui->pathLabel->text().toStdString());
    nlohmann::json j;
    file >> j;
    PageRank p;
    p.calculateEpsilon(j,ui->bText->text().toDouble());
    for(int i(0);i<p.getSize();++i){
        QString strAll = QString::fromStdString(p.getAll(i));
        QString strVp = QString::number(p.getVp(i));
        ui->nameText->append(strAll);
        ui->pRankText->append(strVp);
    }

}

void MainWindow::on_calculateFE_clicked()
{
    ui->nameText->clear();
    ui->pRankText->clear();
    std::ifstream file(ui ->pathLabel->text().toStdString());
    nlohmann::json j;
    file >> j;
    PageRank p;
    p.calculateEpsilonFaulty(j,ui->epsilonText->text().toDouble());
    for(int i(0);i<p.getSize();++i){
        QString strAll = QString::fromStdString(p.getAll(i));
        QString strVp = QString::number(p.getVp(i));
        ui->nameText->append(strAll);
        ui->pRankText->append(strVp);
    }

}

void MainWindow::on_calculateSA_clicked()
{
    ui->nameText->clear();
    ui->pRankText->clear();
    std::ifstream file(ui->pathLabel->text().toStdString());
    nlohmann::json j;
    file >> j;
    PageRank p;
    p.calculate(j,ui->bText->text().toDouble(),ui->iterationsText->text().toDouble(), ui->customPlot);
    p.calculateRankAscending();
    for(int i(0);i<p.getSize();++i){
        QString strAll = QString::fromStdString(p.getAllSecond(i));
        QString strVp = QString::number(p.getAllFirst(i));
        ui->nameText->append(strAll);
        ui->pRankText->append(strVp);
}
}

void MainWindow::on_calculateSD_clicked()
{
    ui->nameText->clear();
    ui->pRankText->clear();
    std::ifstream file(ui->pathLabel->text().toStdString());
    nlohmann::json j;
    file >> j;
    PageRank p;
    p.calculate(j,ui->bText->text().toDouble(),ui->iterationsText->text().toDouble(), ui->customPlot);
    p.calculateRankDescending();
    for(int i(0);i<p.getSize();++i){
        QString strAll = QString::fromStdString(p.getAllSecond(i));
        QString strVp = QString::number(p.getAllFirst(i));
        ui->nameText->append(strAll);
        ui->pRankText->append(strVp);
}
}

