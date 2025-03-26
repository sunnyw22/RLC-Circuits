// Project/circuit.h
// Header file for circuit class declaration
// Wong Kwok Yiu (10453922), Last modified 11/05/2022

#ifndef CIRCUIT_H
#define CIRCUIT_H

#include <complex>
#include <vector>

class circuit
{
private:
    // Circuit parameters
    double AC_voltage{};
    double AC_current{};
    double AC_impedance_magnitude{};
    std::complex<double> AC_impedance{};
    double AC_phase_angle{};

    // Components
    std::vector<circuit*> AC_circuit{nullptr};

public:
    // Constructors
    circuit(){};
    circuit(const std::vector<circuit*>& circuit, double voltage) : AC_circuit{circuit}, AC_voltage{voltage} {};

    // Destructor
    virtual ~circuit(){};

    virtual std::complex<double> impedance();
    virtual double impedance_magnitude();
    virtual double phase_difference();
    virtual double voltage(double current);
    virtual double current(double voltage);
    virtual void print(int type);
    virtual void print_individual(double circuit_current);
};

#endif