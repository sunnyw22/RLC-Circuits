// Project/inductor.h
// Header file for inductor class declaration
// Wong Kwok Yiu (10453922), Last modified 11/05/2022

#ifndef INDUCTOR_H
#define INDUCTOR_H

#include "components.h"
#include <complex>

class inductor : public components
{
private:
    // Unit in Henries
    double inductance;
    // Unit in Hertz
    double frequency;
    double phase;

public:
    // Constructors
    inductor() : inductance{}, frequency{}, phase{} {};
    inductor(double L, double f, double phase) : inductance{L}, frequency{f}, phase{phase} {};
    // Destructor
    virtual ~inductor() {};

    void set_frequency(double new_frequency);
    double get_frequency();
    std::complex<double> impedance();
    double impedance_magnitude();
    double phase_difference();
    double voltage(double current);
    double current(double voltage);
    void print(int type);
    void print_individual(double circuit_current);
};

#endif