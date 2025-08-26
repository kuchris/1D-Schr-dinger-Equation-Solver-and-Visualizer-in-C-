#ifndef SCHRODINGERSOLVER_H
#define SCHRODINGERSOLVER_H

#include <Eigen/Dense>
#include <Eigen/Sparse>
#include <complex>
#include <vector>
#include <fftw3.h>

class SchrodingerSolver
{
public:
    enum SolverMethod {
        CrankNicolson,
        SplitStepFourier
    };

    enum InitialWavePacketType {
        Gaussian,
        PlaneWave
    };

    enum BoundaryConditionType {
        Dirichlet,
        Periodic
    };

    SchrodingerSolver();
    ~SchrodingerSolver();

    void initialize(int size, double dt, double dx, const std::vector<double>& potential, SolverMethod method, InitialWavePacketType wavePacketType, BoundaryConditionType bcType, double sigma, double x0, double k0);
    void step();
    const Eigen::VectorXcd& getWaveFunction() const;

    double calculateExpectationPosition() const;
    double calculateExpectationMomentum() const;
    double calculateExpectationEnergy(const std::vector<double>& potential) const;

    double getDt() const { return m_dt; }

private:
    void stepCrankNicolson();
    void stepSplitStepFourier();
    void normalize(); // New method for normalization

    int m_size;
    double m_dt;
    double m_dx;
    SolverMethod m_method;
    BoundaryConditionType m_bcType; // New member variable

    // For Crank-Nicolson
    Eigen::VectorXcd m_psi; // Wave function
    Eigen::SparseMatrix<std::complex<double>> m_A;
    Eigen::SparseMatrix<std::complex<double>> m_B;
    Eigen::SimplicialLDLT<Eigen::SparseMatrix<std::complex<double>>> m_solver;

    // For Split-Step Fourier
    fftw_complex* m_in;
    fftw_complex* m_out;
    fftw_plan m_plan_forward;
    fftw_plan m_plan_backward;
    Eigen::VectorXcd m_potential_exp_half; // Changed to complex
    Eigen::VectorXcd m_kinetic_exp; // Changed to complex
};

#endif // SCHRODINGERSOLVER_H