// Project/resistor.cpp
// Cpp file for resistor class function definition
// Wong Kwok Yiu (10453922), Last modified 11/05/2022

#include "resistor.h"
#include <complex>
#include <cmath>
#include <iostream>

// Functions for setting new frequency, have not been implemented
void resistor::set_frequency(double new_frequency)
{
    frequency = new_frequency;
    return;
}

// Functions for getting the frequency, have not been implemented
double resistor::get_frequency()
{ 
    return frequency; 
}

std::complex<double> resistor::impedance()
{
    std::complex<double> Z(resistance, 0);
    return Z;
}

double resistor::impedance_magnitude()
{
    return resistance;
}

// Resistor in phase with current
double resistor::phase_difference()
{
    return phase;
}

double resistor::voltage(double current)
{
    double voltage = current * impedance_magnitude();
    return voltage;
}

double resistor::current(double voltage)
{
    double current = voltage / impedance_magnitude();
    return current;
}

void resistor::print_individual(double circuit_current)
{
    return;
}

void resistor::print(int type) 
{
    std::cout<<"--[ ]--";
}