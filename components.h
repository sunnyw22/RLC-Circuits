// Project/components.h
// Header file for abstract class definition
// Wong Kwok Yiu (10453922), Last modified 11/05/2022

#ifndef COMPONENTS_H
#define COMPONENTS_H

#include "circuit.h"
#include <complex>

class components : public circuit
{
public:
    // Virtual destructor
    virtual ~components() {}

    // Pure virtual Functions
    virtual void set_frequency(double new_frequency) = 0;
    virtual double get_frequency() = 0;
    virtual std::complex<double> impedance() = 0;
    virtual double impedance_magnitude() = 0;
    virtual double phase_difference() = 0;
    virtual double voltage(double current) = 0;
    virtual double current(double voltage) = 0;
    virtual void print(int type) = 0;
    virtual void print_individual(double circuit_current) = 0;
};

#endif