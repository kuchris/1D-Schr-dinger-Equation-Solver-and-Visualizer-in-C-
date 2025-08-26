#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QVBoxLayout>
#include <QFileDialog>
#include <iostream> // Added for std::cout
#include <QTextStream>
#include <QtCharts/QValueAxis>
#include <chrono> // Added for std::chrono

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_autoZoomYAxis(true), // Initialize auto zoom state
    m_currentTime(0.0) // Initialize current time
{
    ui->setupUi(this);

    m_series = new QLineSeries();
    m_series->setName("Probability Density");
    m_realSeries = new QLineSeries();
    m_realSeries->setName("Real Part");
    m_imagSeries = new QLineSeries();
    m_imagSeries->setName("Imaginary Part");
    m_potentialSeries = new QLineSeries();
    m_potentialSeries->setName("Potential");

    QChart *chart = new QChart();
    chart->addSeries(m_series);
    chart->addSeries(m_realSeries);
    chart->addSeries(m_imagSeries);
    chart->addSeries(m_potentialSeries);
    chart->createDefaultAxes();
    chart->setTitle("Wave Function");
    ui->chartView->setChart(chart);

    m_timer = new QTimer(this);
    connect(m_timer, &QTimer::timeout, this, &MainWindow::updatePlot);

    ui->methodComboBox->addItem("Crank-Nicolson");
    ui->methodComboBox->addItem("Split-Step Fourier");

    ui->initialWavePacketComboBox->addItem("Gaussian");
    ui->initialWavePacketComboBox->addItem("Plane Wave");

    ui->potentialComboBox->addItem("Zero Potential");
    ui->potentialComboBox->addItem("Harmonic Oscillator");
    ui->potentialComboBox->addItem("Square Well");
    ui->potentialComboBox->addItem("Double Well");

    // Default visibility for real/imag parts
    m_realSeries->setVisible(true);
    m_imagSeries->setVisible(true);
    m_potentialSeries->setVisible(true);

    // Connect auto zoom checkbox
    connect(ui->autoZoomCheckBox, &QCheckBox::toggled, this, &MainWindow::on_autoZoomCheckBox_toggled);

    // Connect plot visibility checkboxes
    connect(ui->probDensityCheckBox, &QCheckBox::toggled, this, &MainWindow::on_probDensityCheckBox_toggled);
    connect(ui->realPartCheckBox, &QCheckBox::toggled, this, &MainWindow::on_realPartCheckBox_toggled);
    connect(ui->imagPartCheckBox, &QCheckBox::toggled, this, &MainWindow::on_imagPartCheckBox_toggled);
    connect(ui->potentialCheckBox, &QCheckBox::toggled, this, &MainWindow::on_potentialCheckBox_toggled);

    // Connect initial wave packet combo box
    connect(ui->initialWavePacketComboBox, static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this, &MainWindow::on_initialWavePacketComboBox_currentIndexChanged);

    // Connect pause/resume button
    connect(ui->pauseResumeButton, &QPushButton::clicked, this, &MainWindow::on_pauseResumeButton_clicked);

    // Connect reset button
    connect(ui->resetButton, &QPushButton::clicked, this, &MainWindow::on_resetButton_clicked);

    // Initialize expectation value labels
    ui->expectationPositionLabel->setText("Expectation Position <x>:");
    ui->expectationMomentumLabel->setTextFormat(Qt::PlainText);
    ui->expectationEnergyLabel->setText("Expectation Energy <H>:");
    ui->timeLabel->setText("Time: 0.0");

    // Initialize solver with default UI parameters
    int size = ui->sizeSpinBox->value();
    double dt = ui->dtSpinBox->value();
    double dx = ui->dxSpinBox->value();
    double sigma = ui->sigmaSpinBox->value();
    double x0 = ui->x0SpinBox->value();
    double k0 = ui->k0SpinBox->value();

    m_potential.assign(size, 0.0); // Initialize m_potential to all zeros for default
    SchrodingerSolver::SolverMethod method = (SchrodingerSolver::SolverMethod)ui->methodComboBox->currentIndex();
    SchrodingerSolver::InitialWavePacketType wavePacketType = (SchrodingerSolver::InitialWavePacketType)ui->initialWavePacketComboBox->currentIndex();

    m_solver.initialize(size, dt, dx, m_potential, method, wavePacketType, SchrodingerSolver::Dirichlet, sigma, x0, k0);

    // Initialize plot and expectation values
    updatePlot();

    // Set initial visibility of wave packet parameters
    on_initialWavePacketComboBox_currentIndexChanged(ui->initialWavePacketComboBox->currentIndex());
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_startButton_clicked()
{
    std::cout << "Start button clicked." << std::endl;
    int size = ui->sizeSpinBox->value();
    double dt = ui->dtSpinBox->value();
    double dx = ui->dxSpinBox->value();

    m_potential.assign(size, 0.0); // Initialize m_potential
    if (ui->potentialComboBox->currentText() == "Harmonic Oscillator") {
        for (int i = 0; i < size; ++i) {
            double x = i * dx - size * dx / 2.0;
            m_potential[i] = 0.5 * x * x;
        }
    } else if (ui->potentialComboBox->currentText() == "Square Well") {
        for (int i = 0; i < size; ++i) {
            if (i > size / 4 && i < 3 * size / 4) {
                m_potential[i] = -100;
            }
        }
    } else if (ui->potentialComboBox->currentText() == "Double Well") {
        for (int i = 0; i < size; ++i) {
            double x = i * dx - size * dx / 2.0;
            m_potential[i] = 0.01 * (x * x * x * x - 50 * x * x);
        }
    }

    SchrodingerSolver::SolverMethod method = (SchrodingerSolver::SolverMethod)ui->methodComboBox->currentIndex();
    SchrodingerSolver::InitialWavePacketType wavePacketType = (SchrodingerSolver::InitialWavePacketType)ui->initialWavePacketComboBox->currentIndex();
    double sigma = ui->sigmaSpinBox->value();
    double x0 = ui->x0SpinBox->value();
    double k0 = ui->k0SpinBox->value();
    m_solver.initialize(size, dt, dx, m_potential, method, wavePacketType, SchrodingerSolver::Dirichlet, sigma, x0, k0);
    m_timer->start(16); // ~60 fps
    std::cout << "Timer started in on_startButton_clicked(). isActive(): " << m_timer->isActive() << std::endl;
    ui->pauseResumeButton->setText("Pause"); // Ensure button says Pause when simulation starts
    ui->pauseResumeButton->setEnabled(false); // Disable pause/resume button
}

void MainWindow::on_saveDataButton_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save Data"), "", tr("CSV Files (*.csv)"));
    if (fileName.isEmpty()) {
        return;
    }

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        return;
    }

    QTextStream out(&file);
    out << "x,real(psi),imag(psi),norm(psi)\n";

    const auto& psi = m_solver.getWaveFunction();
    for (int i = 0; i < psi.size(); ++i) {
        out << i * ui->dxSpinBox->value() << "," << psi[i].real() << "," << psi[i].imag() << "," << std::norm(psi[i]) << "\n";
    }
}

void MainWindow::on_pauseResumeButton_clicked()
{
    std::cout << "Pause/Resume button clicked. Timer isActive() before: " << m_timer->isActive() << std::endl;
    if (m_timer->isActive()) {
        m_timer->stop();
        ui->pauseResumeButton->setText("Resume");
        std::cout << "Timer stopped. isActive(): " << m_timer->isActive() << std::endl;
    } else {
        m_timer->start(16);
        ui->pauseResumeButton->setText("Pause");
        std::cout << "Timer started. isActive(): " << m_timer->isActive() << std::endl;
    }
}

void MainWindow::on_resetButton_clicked()
{
    std::cout << "Reset button clicked." << std::endl;
    m_timer->stop();
    m_currentTime = 0.0;
    ui->pauseResumeButton->setText("Pause"); // Reset button text
    ui->pauseResumeButton->setEnabled(false); // Disable pause/resume button

    // Re-initialize the solver with current UI parameters
    int size = ui->sizeSpinBox->value();
    double dt = ui->dtSpinBox->value();
    double dx = ui->dxSpinBox->value();

    m_potential.assign(size, 0.0); // Initialize m_potential
    if (ui->potentialComboBox->currentText() == "Harmonic Oscillator") {
        for (int i = 0; i < size; ++i) {
            double x = i * dx - size * dx / 2.0;
            m_potential[i] = 0.5 * x * x;
        }
    } else if (ui->potentialComboBox->currentText() == "Square Well") {
        for (int i = 0; i < size; ++i) {
            if (i > size / 4 && i < 3 * size / 4) {
                m_potential[i] = -100;
            }
        }
    } else if (ui->potentialComboBox->currentText() == "Double Well") {
        for (int i = 0; i < size; ++i) {
            double x = i * dx - size * dx / 2.0;
            m_potential[i] = 0.01 * (x * x * x * x - 50 * x * x);
        }
    }

    SchrodingerSolver::SolverMethod method = (SchrodingerSolver::SolverMethod)ui->methodComboBox->currentIndex();
    SchrodingerSolver::InitialWavePacketType wavePacketType = (SchrodingerSolver::InitialWavePacketType)ui->initialWavePacketComboBox->currentIndex();
    double sigma = ui->sigmaSpinBox->value();
    double x0 = ui->x0SpinBox->value();
    double k0 = ui->k0SpinBox->value();
    m_solver.initialize(size, dt, dx, m_potential, method, wavePacketType, SchrodingerSolver::Dirichlet, sigma, x0, k0);

    updatePlot(); // Update plot and labels immediately after reset
}



void MainWindow::on_autoZoomCheckBox_toggled(bool checked)
{
    m_autoZoomYAxis = checked;
}

void MainWindow::on_probDensityCheckBox_toggled(bool checked)
{
    m_series->setVisible(checked);
}

void MainWindow::on_realPartCheckBox_toggled(bool checked)
{
    m_realSeries->setVisible(checked);
}

void MainWindow::on_imagPartCheckBox_toggled(bool checked)
{
    m_imagSeries->setVisible(checked);
}

void MainWindow::on_potentialCheckBox_toggled(bool checked)
{
    m_potentialSeries->setVisible(checked);
}

void MainWindow::on_initialWavePacketComboBox_currentIndexChanged(int index)
{
    // Gaussian is index 0, PlaneWave is index 1
    bool isGaussian = (index == SchrodingerSolver::Gaussian);

    ui->sigmaLabel->setVisible(isGaussian);
    ui->sigmaSpinBox->setVisible(isGaussian);
    ui->x0Label->setVisible(isGaussian);
    ui->x0SpinBox->setVisible(isGaussian);

    ui->k0Label->setVisible(!isGaussian);
    ui->k0SpinBox->setVisible(!isGaussian);
}

void MainWindow::updatePlot()
{
    auto start = std::chrono::high_resolution_clock::now();
    std::cout << "updatePlot() called. Timer isActive(): " << m_timer->isActive() << std::endl;

    m_solver.step();
    m_currentTime += m_solver.getDt(); // Increment time

    const auto& psi = m_solver.getWaveFunction();

    QVector<QPointF> points;
    QVector<QPointF> realPoints;
    QVector<QPointF> imagPoints;
    double maxVal = 0.0; // To find the maximum for auto-scaling
    double minVal = 0.0; // To find the minimum for auto-scaling

    for (int i = 0; i < psi.size(); ++i) {
        double x = i * ui->dxSpinBox->value();
        double psiNorm = std::norm(psi[i]);
        double psiReal = psi[i].real();
        double psiImag = psi[i].imag();

        points.append(QPointF(x, psiNorm));
        realPoints.append(QPointF(x, psiReal));
        imagPoints.append(QPointF(x, psiImag));

        // Update max/min for auto-scaling
        if (psiNorm > maxVal) maxVal = psiNorm;
        if (psiReal > maxVal) maxVal = psiReal;
        if (psiImag > maxVal) maxVal = psiImag;
        if (psiReal < minVal) minVal = psiReal;
        if (psiImag < minVal) minVal = psiImag;
    }
    m_series->replace(points);
    m_realSeries->replace(realPoints);
    m_imagSeries->replace(imagPoints);

    // Always set X-axis range
    ui->chartView->chart()->axisX()->setRange(0, psi.size() * ui->dxSpinBox->value());

    // Always auto-scale Y-axis with margin
    if (m_autoZoomYAxis) {
        ui->chartView->chart()->axisY()->setRange(minVal * 1.1, maxVal * 1.1);
    }

    // Update potential series
    QVector<QPointF> potentialPoints;
    for (int i = 0; i < m_potential.size(); ++i) {
        double x = i * ui->dxSpinBox->value();
        potentialPoints.append(QPointF(x, m_potential[i]));
    }
    m_potentialSeries->replace(potentialPoints);

    // Update expectation values
    ui->expectationPositionLabel->setText(QString("Expectation Position <x>: %1").arg(m_solver.calculateExpectationPosition(), 0, 'f', 6));
    ui->expectationMomentumLabel->setText(QString("Expectation Momentum <p>: %1").arg(m_solver.calculateExpectationMomentum(), 0, 'f', 6));
    ui->expectationEnergyLabel->setText(QString("Expectation Energy <H>: %1").arg(m_solver.calculateExpectationEnergy(m_potential), 0, 'f', 6));
    ui->timeLabel->setText(QString("Time: %1").arg(m_currentTime, 0, 'f', 6));

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duration = end - start;
    std::cout << "updatePlot() execution time: " << duration.count() << " ms" << std::endl;
}
