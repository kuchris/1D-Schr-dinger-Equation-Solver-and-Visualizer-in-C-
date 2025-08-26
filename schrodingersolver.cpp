#define _USE_MATH_DEFINES
#include <cmath>
#include "schrodingersolver.h"
#include <iostream>
#include <chrono> // Added for std::chrono

SchrodingerSolver::SchrodingerSolver() : m_size(0), m_dt(0), m_dx(0), m_in(nullptr), m_out(nullptr) {}

SchrodingerSolver::~SchrodingerSolver()
{
    if (m_in) fftw_free(m_in);
    if (m_out) fftw_free(m_out);
}

void SchrodingerSolver::initialize(int size, double dt, double dx, const std::vector<double>& potential, SolverMethod method, InitialWavePacketType wavePacketType, BoundaryConditionType bcType, double sigma, double x0, double k0)
{
    m_size = size;
    m_dt = dt;
    m_dx = dx;
    m_method = method;
    m_bcType = bcType;

    m_psi.resize(m_size);

    if (wavePacketType == Gaussian) {
        for (int i = 0; i < m_size; ++i) {
            double x = i * m_dx;
            m_psi[i] = std::exp(-std::pow(x - x0, 2) / (2 * sigma * sigma));
        }
    } else if (wavePacketType == PlaneWave) {
        for (int i = 0; i < m_size; ++i) {
            double x = i * m_dx;
            m_psi[i] = std::exp(std::complex<double>(0, 1) * k0 * x);
        }
    }

    // Apply boundary conditions to initial wave packet
    if (m_bcType == Dirichlet) {
        m_psi[0] = 0;
        m_psi[m_size - 1] = 0;
    }

    if (m_method == CrankNicolson) {
        m_A.resize(m_size, m_size);
        m_B.resize(m_size, m_size);

        std::vector<Eigen::Triplet<std::complex<double>>> tripletsA;
        std::vector<Eigen::Triplet<std::complex<double>>> tripletsB;

        std::complex<double> i_unit(0, 1);
        double s = 1.0 / (m_dx * m_dx);

        if (m_bcType == Dirichlet) {
            tripletsA.push_back(Eigen::Triplet<std::complex<double>>(0, 0, 1.0));
            tripletsB.push_back(Eigen::Triplet<std::complex<double>>(0, 0, 1.0));

            for (int j = 1; j < m_size - 1; ++j) {
                tripletsA.push_back(Eigen::Triplet<std::complex<double>>(j, j, 1.0 + i_unit * m_dt * (s + potential[j]) / 2.0));
                tripletsA.push_back(Eigen::Triplet<std::complex<double>>(j, j - 1, -i_unit * m_dt * s / 4.0));
                tripletsA.push_back(Eigen::Triplet<std::complex<double>>(j, j + 1, -i_unit * m_dt * s / 4.0));

                tripletsB.push_back(Eigen::Triplet<std::complex<double>>(j, j, 1.0 - i_unit * m_dt * (s + potential[j]) / 2.0));
                tripletsB.push_back(Eigen::Triplet<std::complex<double>>(j, j - 1, i_unit * m_dt * s / 4.0));
                tripletsB.push_back(Eigen::Triplet<std::complex<double>>(j, j + 1, i_unit * m_dt * s / 4.0));
            }

            tripletsA.push_back(Eigen::Triplet<std::complex<double>>(m_size - 1, m_size - 1, 1.0));
            tripletsB.push_back(Eigen::Triplet<std::complex<double>>(m_size - 1, m_size - 1, 1.0));
        } else if (m_bcType == Periodic) {
            for (int j = 0; j < m_size; ++j) {
                tripletsA.push_back(Eigen::Triplet<std::complex<double>>(j, j, 1.0 + i_unit * m_dt * (s + potential[j]) / 2.0));
                tripletsB.push_back(Eigen::Triplet<std::complex<double>>(j, j, 1.0 - i_unit * m_dt * (s + potential[j]) / 2.0));

                // Off-diagonal terms
                tripletsA.push_back(Eigen::Triplet<std::complex<double>>(j, (j - 1 + m_size) % m_size, -i_unit * m_dt * s / 4.0));
                tripletsA.push_back(Eigen::Triplet<std::complex<double>>(j, (j + 1) % m_size, -i_unit * m_dt * s / 4.0));

                tripletsB.push_back(Eigen::Triplet<std::complex<double>>(j, (j - 1 + m_size) % m_size, i_unit * m_dt * s / 4.0));
                tripletsB.push_back(Eigen::Triplet<std::complex<double>>(j, (j + 1) % m_size, i_unit * m_dt * s / 4.0));
            }
        }

        m_A.setFromTriplets(tripletsA.begin(), tripletsA.end());
        m_B.setFromTriplets(tripletsB.begin(), tripletsB.end());

        m_solver.compute(m_A);
        if(m_solver.info() != Eigen::Success) {
            std::cerr << "Decomposition failed" << std::endl;
            return;
        }
    } else if (m_method == SplitStepFourier) {
        m_in = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * m_size);
        m_out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * m_size);
        m_plan_forward = fftw_plan_dft_1d(m_size, m_in, m_out, FFTW_FORWARD, FFTW_ESTIMATE);
        m_plan_backward = fftw_plan_dft_1d(m_size, m_out, m_in, FFTW_BACKWARD, FFTW_ESTIMATE);

        m_potential_exp_half.resize(m_size);
        m_kinetic_exp.resize(m_size);

        std::complex<double> i_unit(0, 1);
        for (int j = 0; j < m_size; ++j) {
            m_potential_exp_half[j] = std::exp(-i_unit * potential[j] * m_dt / 2.0);
        }

        double L = m_size * m_dx;
        for (int j = 0; j < m_size; ++j) {
            double k;
            if (j < m_size / 2) {
                k = 2.0 * M_PI * j / L;
            } else {
                k = 2.0 * M_PI * (j - m_size) / L;
            }
            m_kinetic_exp[j] = std::exp(-i_unit * k * k * m_dt);
        }
    }
}

void SchrodingerSolver::step()
{
    auto start = std::chrono::high_resolution_clock::now();
    std::cout << "SchrodingerSolver::step() called." << std::endl;
    if (m_method == CrankNicolson) {
        stepCrankNicolson();
    } else if (m_method == SplitStepFourier) {
        stepSplitStepFourier();
    }
    normalize(); // Normalize after each step
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duration = end - start;
    std::cout << "SchrodingerSolver::step() execution time: " << duration.count() << " ms" << std::endl;
}

void SchrodingerSolver::stepCrankNicolson()
{
    if (m_size == 0) return;

    Eigen::VectorXcd rhs = m_B * m_psi;
    m_psi = m_solver.solve(rhs);
    if(m_solver.info() != Eigen::Success) {
        std::cerr << "Solving failed" << std::endl;
        return;
    }
}

void SchrodingerSolver::stepSplitStepFourier()
{
    if (m_size == 0) return;

    // Propagate in position space (half step)
    for (int i = 0; i < m_size; ++i) {
        m_psi[i] *= m_potential_exp_half[i];
    }

    // FFT to momentum space
    for (int i = 0; i < m_size; ++i) {
        m_in[i][0] = m_psi[i].real();
        m_in[i][1] = m_psi[i].imag();
    }
    fftw_execute(m_plan_forward);

    // Propagate in momentum space
    for (int i = 0; i < m_size; ++i) {
        std::complex<double> c(m_out[i][0], m_out[i][1]);
        c *= m_kinetic_exp[i];
        m_out[i][0] = c.real();
        m_out[i][1] = c.imag();
    }

    // IFFT back to position space
    fftw_execute(m_plan_backward);

    // Propagate in position space (half step)
    for (int i = 0; i < m_size; ++i) {
        m_psi[i] = std::complex<double>(m_in[i][0], m_in[i][1]) / (double)m_size;
        m_psi[i] *= m_potential_exp_half[i];
    }
}

void SchrodingerSolver::normalize()
{
    double norm_squared = 0.0;
    for (int i = 0; i < m_size; ++i) {
        norm_squared += std::norm(m_psi[i]);
    }
    double norm = std::sqrt(norm_squared * m_dx);
    if (norm > 1e-10) { // Avoid division by zero or very small numbers
        m_psi /= norm;
    }
}

double SchrodingerSolver::calculateExpectationPosition() const
{
    double expectation = 0.0;
    for (int i = 0; i < m_size; ++i) {
        double x = i * m_dx;
        expectation += x * std::norm(m_psi[i]);
    }
    return expectation * m_dx;
}

double SchrodingerSolver::calculateExpectationMomentum() const
{
    double expectation = 0.0;
    std::complex<double> i_unit(0, 1);
    for (int j = 1; j < m_size - 1; ++j) {
        std::complex<double> derivative = (m_psi[j+1] - m_psi[j-1]) / (2.0 * m_dx);
        expectation += std::real(std::conj(m_psi[j]) * (-i_unit * derivative));
    }
    return expectation * m_dx;
}

double SchrodingerSolver::calculateExpectationEnergy(const std::vector<double>& potential) const
{
    double expectation = 0.0;
    for (int j = 1; j < m_size - 1; ++j) {
        std::complex<double> second_derivative = (m_psi[j+1] - 2.0 * m_psi[j] + m_psi[j-1]) / (m_dx * m_dx);
        std::complex<double> kinetic_term = -0.5 * second_derivative; // Assuming hbar=1, m=1
        std::complex<double> potential_term = potential[j] * m_psi[j];
        expectation += std::real(std::conj(m_psi[j]) * (kinetic_term + potential_term));
    }
    return expectation * m_dx;
}

const Eigen::VectorXcd& SchrodingerSolver::getWaveFunction() const
{
    return m_psi;
}
