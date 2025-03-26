// Project/inductor.cpp
// Cpp file for inductor class function definition
// Wong Kwok Yiu (10453922), Last modified 11/05/2022

#include "inductor.h"
#include <complex>
#include <cmath>
#include <iostream>

// Functions for setting new frequency, have not been implemented
void inductor::set_frequency(double new_frequency)
{
    frequency = new_frequency;
    return;
}

// Functions for getting the frequency, have not been implemented
double inductor::get_frequency()
{
    return frequency;
}

std::complex<double> inductor::impedance()
{
    double inductive_reactance = 2 * M_PI * frequency * inductance;
    std::complex<double> Z(0, inductive_reactance);
    return Z;
}

double inductor::impedance_magnitude()
{
    double inductive_reactance = 2 * M_PI * frequency * inductance;
    std::complex<double> Z(0, inductive_reactance);
    return std::abs(Z);
}

// Inductor leads the current by 90 degrees
double inductor::phase_difference()
{
    return phase + 90;
}

double inductor::voltage(double current)
{
    double voltage = current * impedance_magnitude();
    return voltage;
}

double inductor::current(double voltage)
{
    double current = voltage / impedance_magnitude();
    return current;
}

void inductor::print_individual(double circuit_current)
{
    return;
}

void inductor::print(int type)
{
    std::cout << "--xxx--";
}
