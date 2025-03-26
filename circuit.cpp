// Project/circuit.cpp
// Cpp file for circuit class function definition
// Wong Kwok Yiu (10453922), Last modified 11/05/2022

#include "circuit.h"
#include <complex>
#include <cmath>
#include <vector>
#include <iostream>

// Calculate and store the impedance of the circuit
std::complex<double> circuit::impedance()
{
    std::complex<double> Z;
    for (auto AC_circuit : AC_circuit)
    {
        Z += AC_circuit->impedance();
    }
    AC_impedance = Z;
    return Z;
}

// Return and store the impedance magnitude of the circuit
double circuit::impedance_magnitude()
{
    AC_impedance_magnitude = std::abs(AC_impedance);
    return AC_impedance_magnitude;
}

// Return the phase shift of circuit
double circuit::phase_difference()
{
    AC_phase_angle = std::arg(AC_impedance)*180/M_PI;
    return AC_phase_angle;
}

double circuit::voltage(double current)
{
    double voltage = current * impedance_magnitude();
    return voltage;
}

double circuit::current(double voltage)
{
    AC_current = AC_voltage / AC_impedance_magnitude;
    return AC_current;
}

// Function to print individual component information, including voltage/current across the component and phase shift
void circuit::print_individual(double circuit_current)
{
    std::cout << "======== Individual component information ========" << std::endl;
    for (int i{}; i<AC_circuit.size(); i++)
    {
        std::cout << "For circuit part " << i+1 << ":" << std::endl;
        std::cout << "---------------------------- " << std::endl;
        AC_circuit[i]->print_individual(circuit_current);
        std::cout << std::endl;
    }
}

// Printing circuit information
void circuit::print(int type)
{   
    std::cout << std::endl; 
    std::cout << "======== Circuit built ========" << std::endl;
    std::cout << "Circuit properties:" << std::endl;
    std::cout << "-------------------" << std::endl;
    std::cout << "Impedance expressed in (real, imaginary):" << std::endl;
    std::cout << "Circuit impedance = " << impedance() << std::endl;
    std::cout << "Impedance magnitude (in ohms) = " << impedance_magnitude() << std::endl;
    std::cout << "Current across the circuit (in Amps) = " << current(0) << std::endl;
    std::cout << "Phase angle (in degrees) = " << phase_difference() << std::endl;
    std::cout << "*positive phase angle means lagging the voltage, negative means leading" << std::endl;
    std::cout << std::endl;
    
    if (type == 1 || type == 2)
    {
        std::cout << "Printing the constructed circuit: " << std::endl;
        std::cout << "Components information (print):" << std::endl;
        std::cout << "----------" << std::endl;
        std::cout << "A resistor is denoted as --[ ]--" << std::endl;
        std::cout << "An inductor is denoted as --xxx--" << std::endl;
        std::cout << "A capacitor is denoted as --| |--" << std::endl;
        std::cout << "----------" << std::endl;
        std::cout << std::endl;
        
        if (type == 1)
        {
            std::cout << "--o ";
            for (auto AC_circuit : AC_circuit)
            {
                AC_circuit->print(0);
            }
            std::cout << " o--" << std::endl;
            std::cout << std::endl;
        }

        if (type == 2)
        {
            for (auto AC_circuit : AC_circuit)
            {
                AC_circuit->print(0);
            }
            std::cout << std::endl;
        }
    }
    print_individual(AC_current);
}