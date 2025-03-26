// Project/series.h
// Header file for series class declaration
// Wong Kwok Yiu (10453922), Last modified 11/05/2022

#ifndef SERIES_H
#define SERIES_H

#include "../circuit.h" 
#include <vector>
#include <complex>
#include <memory>

class series : public circuit
{
private:
    // Storing components in each branch
    std::vector<std::shared_ptr<circuit>> series_branch;
    std::complex<double> series_impedance;
    
public:
    /// Constructors
    series() : series_branch{nullptr}, series_impedance{} {};
    series(const std::vector<std::shared_ptr<circuit>>& branch) : series_branch{branch}, series_impedance{} {};

    // Destructor
    virtual ~series() {};

    std::complex<double> impedance();
    double impedance_magnitude();
    double phase_difference();
    double voltage(double current);
    double current(double voltage);
    void print(int type);
    void print_individual(double circuit_current);
};

#endif