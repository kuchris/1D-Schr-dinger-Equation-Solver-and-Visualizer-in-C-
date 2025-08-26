#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCharts/QLineSeries>
#include <QTimer>
#include "schrodingersolver.h"
#include <vector>

QT_CHARTS_USE_NAMESPACE

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_startButton_clicked();
    void on_pauseResumeButton_clicked(); // New slot for pause/resume
    void on_resetButton_clicked(); // New slot for reset
    void on_saveDataButton_clicked();
    void updatePlot();
    void on_autoZoomCheckBox_toggled(bool checked);
    void on_probDensityCheckBox_toggled(bool checked);
    void on_realPartCheckBox_toggled(bool checked);
    void on_imagPartCheckBox_toggled(bool checked);
    void on_potentialCheckBox_toggled(bool checked);
    void on_initialWavePacketComboBox_currentIndexChanged(int index);

private:
    Ui::MainWindow *ui;
    QLineSeries *m_series; // For probability density
    QLineSeries *m_realSeries; // For real part
    QLineSeries *m_imagSeries; // For imaginary part
    QLineSeries *m_potentialSeries; // For potential
    SchrodingerSolver m_solver;
    QTimer *m_timer;
    std::vector<double> m_potential; // Store potential for energy calculation
    bool m_autoZoomYAxis; // New member for auto zoom state
    double m_currentTime; // New member for current simulation time
};

#endif // MAINWINDOW_H