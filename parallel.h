// Project/parallel.h
// Header file for parallel class declaration
// Wong Kwok Yiu (10453922), Last modified 11/05/2022

#ifndef PARALLEL_H
#define PARALLEL_H

#include "circuit.h" 
#include <vector>
#include <complex>
#include <memory>

class parallel : public circuit
{
private:
    // Storing components in each branch
    std::vector<std::shared_ptr<circuit>> parallel_branch;
    std::complex<double> parallel_impedance;
    
public:
    /// Constructors
    parallel() : parallel_branch{nullptr}, parallel_impedance{} {};
    parallel(const std::vector<std::shared_ptr<circuit>>& branch) : parallel_branch{branch}, parallel_impedance{} {};

    // Destructor
    virtual ~parallel() {};

    std::complex<double> impedance();
    double impedance_magnitude();
    double phase_difference();
    double voltage(double current);
    double current(double voltage);
    void print(int type);
    void print_individual(double circuit_current);
};

#endif