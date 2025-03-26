// Project/parallel.cpp
// Cpp file for parallel class function definition
// Wong Kwok Yiu (10453922), Last modified 11/05/2022

#include "parallel.h"
#include <iostream>
#include <vector>
#include <complex>
#include <cmath>

// Function to calculate and store parallel part impedance
std::complex<double> parallel::impedance()
{
    std::complex<double> Z{};
    std::complex<double> inverse_impedance{};
    std::complex<double> unity(1,0);
    for (auto parallel_branch : parallel_branch)
    {   
        std::complex<double> component_impedance{};
        component_impedance = parallel_branch->impedance();
        inverse_impedance += unity/component_impedance;
    }
    Z = unity/inverse_impedance;
    parallel_impedance = Z;
    return Z;
}

// Return impedance magnitude of the parallel part
double parallel::impedance_magnitude()
{
    return std::abs(parallel_impedance);
}

// Return phase shift of the parallel circuit
double parallel::phase_difference()
{
    return std::arg(parallel_impedance)*180/M_PI;
}

double parallel::voltage(double current)
{ 
    double voltage = current * impedance_magnitude();
    return voltage;
}

double parallel::current(double voltage)
{
    double current = voltage / impedance_magnitude();
    return current;
}

// Function to output individual component information
void parallel::print_individual(double circuit_current)
{
    // voltage shared across this parallel part
    double parallel_voltage = circuit_current * impedance_magnitude();
    std::cout << "For this parallel part: " << std::endl;
    std::cout << "Voltage across the whole parallel part (branches share the same voltage) = " << parallel_voltage << " V " << std::endl;
    std::cout << "Current across the whole parallel part = " << circuit_current << " A " << std::endl;
    std::cout << std::endl;
    for (int i{}; i<parallel_branch.size(); i++)
    {
        std::cout << "Information for branch " << i+1 << ":" << std::endl; 
        std::cout << "------------------------ " << std::endl;
        double branch_current = parallel_voltage / parallel_branch[i]->impedance_magnitude();
        parallel_branch[i]->print_individual(branch_current);
        std::cout << std::endl;
    }
}

// Function to output parallel circuit information
void parallel::print(int type)
{
    for (int i{}; i<parallel_branch.size(); i++)
    {
        if (i!=0)
        {
            if (i==std::floor(parallel_branch.size()/2) && parallel_branch.size()%2==0)
            {
                std::cout << "--o|" << std::endl;    
            }
            else 
            {
                std::cout << "   |" << std::endl;
            }
        }

        if (i==std::floor(parallel_branch.size()/2) && parallel_branch.size()%2!=0)
        {
            std::cout << "--o ";
        }
        else
        {
            std::cout << "    ";
        }

        parallel_branch[i]->print(0);

        std::cout << std::endl;
    }
}