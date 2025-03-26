// Project/capacitor.cpp
// Cpp file for capacitor class function definition
// Wong Kwok Yiu (10453922), Last modified 11/05/2022

#include "capacitor.h"
#include <complex>
#include <cmath>
#include <iostream>

// Functions for setting new frequency, have not been implemented
void capacitor::set_frequency(double new_frequency)
{
    frequency = new_frequency;
    return;
}

// Functions for getting the frequency, have not been implemented
double capacitor::get_frequency()
{ 
    return frequency; 
}

std::complex<double> capacitor::impedance()
{
    double capacitive_reactance = 1 / (2 * M_PI * frequency * capacitance);
    std::complex<double> Z(0, -1*capacitive_reactance);
    return Z;
}

double capacitor::impedance_magnitude()
{
    double capacitive_reactance = 1 / (2 * M_PI * frequency * capacitance);
    std::complex<double> Z(0, capacitive_reactance);
    return std::abs(Z);
}

// Capacitor lacks the voltage by 90 degrees
double capacitor::phase_difference()
{
    return phase - 90;
}

double capacitor::voltage(double current)
{
    double voltage = current * impedance_magnitude();
    return voltage;
}

double capacitor::current(double voltage)
{
    double current = voltage / impedance_magnitude();
    return current;
}

void capacitor::print_individual(double circuit_current)
{
    return;
}

void capacitor::print(int type) 
{
    std::cout<<"--| |--";
}