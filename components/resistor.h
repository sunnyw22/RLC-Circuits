// Project/resistor.h
// Header file for resistor class declaration
// Wong Kwok Yiu (10453922), Last modified 11/05/2022

#ifndef RESISTOR_H
#define RESISTOR_H

#include "components.h"
#include <complex>

class resistor : public components
{
private:
    // Unit in Ohms
    double resistance;
    // Unit in Hertz
    double frequency;
    double phase;

public:
    // Constructors
    resistor() : resistance{}, frequency{}, phase{} {};
    resistor(double R, double f, double phase) : resistance{R}, frequency{f}, phase{phase} {};
    // Destructor
    virtual ~resistor() {};

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