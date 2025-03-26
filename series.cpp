// Project/series.cpp
// Cpp file for series class function definition
// Wong Kwok Yiu (10453922), Last modified 11/05/2022

#include "series.h"
#include <complex>
#include <iostream>
#include <vector>
#include <cmath>

// Function to calculate and store serial part impedance
std::complex<double> series::impedance()
{
    std::complex<double> Z;
    for (auto series_branch : series_branch)
    {
        Z += series_branch->impedance();
    }
    series_impedance = Z;
    return Z;
}

// Return impedance magnitude of the serial part
double series::impedance_magnitude()
{
    return std::abs(series_impedance);
}

// Return phase shift of the serial circuit
double series::phase_difference()
{
    return std::arg(series_impedance)*180/M_PI;
}

double series::voltage(double current)
{
    double voltage = current * impedance_magnitude();
    return voltage;
}

double series::current(double voltage)
{
    double current = voltage / impedance_magnitude();
    return current;
}

// Function to output individual component information
void series::print_individual(double circuit_current)
{
    // voltage shared across this series part
    double series_voltage = circuit_current * impedance_magnitude();
    std::cout << "For this serial part/branch: " << std::endl;
    std::cout << "Voltage across the whole serial part = " << series_voltage << " V " << std::endl;
    std::cout << "Current across the whole serial part (components share the same current) = " << circuit_current << " A " << std::endl;
    std::cout << std::endl;
    for (int i{}; i<series_branch.size(); i++)
    {
        std::cout << "Phase shift for component " << i+1 << ": " << series_branch[i]->phase_difference() << std::endl;
        std::cout << "Voltage across component " << i+1 << ": " << series_branch[i]->voltage(circuit_current) << " V " << std::endl;
    }
}

// Function to output parallel circuit information
void series::print(int type)
{
    for (auto series_branch : series_branch)
    {
        series_branch->print(0);
    }
}