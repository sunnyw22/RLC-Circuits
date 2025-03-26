// Project/capacitor.h
// Header file for capacitor class declaration
// Wong Kwok Yiu (10453922), Last modified 11/05/2022

#ifndef CAPACITOR_H
#define CAPACITOR_H

#include "components.h"
#include <complex>

class capacitor : public components
{
private:
    // Unit in Farads
    double capacitance;
    // Unit in Hertz
    double frequency;
    double phase;

public:
    // Constructors
    capacitor() : capacitance{}, frequency{}, phase{} {};
    capacitor(double C, double f, double phase) : capacitance{C}, frequency{f}, phase{phase} {};
    // Destructor
    virtual ~capacitor() {};

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