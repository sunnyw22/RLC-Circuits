// Project/project.cpp
// Main file for the AC-circuit project, this programme computes the AC circuit impedance,
// impedance magnitude, circuit phase shift, information for individual components and 
// prints out the constructed circuit. Required input for the programme are supply voltage,
// supply frequency and phase.
// Wong Kwok Yiu (10453922), Last modified 11/05/2022

#include "circuit.h"
#include "components.h"
#include "resistor.h"
#include "inductor.h"
#include "capacitor.h"
#include "series.h"
#include "parallel.h"

#include <iostream>
#include <string>
#include <complex>
#include <cmath>
#include <memory>
#include <vector>

// Function to build a series part of the circuit
std::vector<std::shared_ptr<circuit>> build_series(double frequency, double phase)
{
    // vector of base class shared pointers to store constructed objects in this series part
    std::vector<std::shared_ptr<circuit>> series_vector;
    int no_of_components;
    std::cout << "Enter the number of components: " << std::endl;
    std::cin >> no_of_components;

    for (int i = 0; i < no_of_components; i++)
    {
        std::cout << "Component " << i + 1 << ":" << std::endl;
        std::cout << "Enter 1 for a resistor, 2 for a inductor, 3 for a capacitor." << std::endl;
        int component_type{};
        std::cin >> component_type;
        std::cin.clear();
        std::cin.ignore();
        if (component_type == 1)
        {
            double R{};
            std::cout << "Enter the resistance (unit of ohm) of resistor: " << std::endl;
            std::cin >> R;
            std::shared_ptr<circuit> temp_resistor(new resistor(R, frequency, phase));
            series_vector.push_back(std::move(temp_resistor));
        }
        else if (component_type == 2)
        {
            double L{};
            std::cout << "Enter the inductance (unit of henries) of inductor " << std::endl;
            std::cin >> L;
            std::shared_ptr<circuit> temp_inductor(new inductor(L, frequency, phase));
            series_vector.push_back(std::move(temp_inductor));
        }
        else if (component_type == 3)
        {
            double C{};
            std::cout << "Enter the capacitance (unit of mu Farad) of capacitor " << std::endl;
            std::cin >> C;
            std::shared_ptr<circuit> temp_capacitor(new capacitor(C * pow(10, -6), frequency, phase));
            series_vector.push_back(std::move(temp_capacitor));
        }
        else
        {
            std::cout << "Invalid input, please try again." << std::endl;
            i -= 1;
        }
    }
    return series_vector;
}

std::vector<std::shared_ptr<circuit>> build_parallel(double frequency, double phase, int no_of_branches)
{
    // vector of base class shared pointers to store constructed objects in this parallel part
    std::vector<std::shared_ptr<circuit>> parallel_vector;
    for (int i{}; i < no_of_branches; i++)
    {
        std::cout << "For branch " << i + 1 << ":" << std::endl;
        std::shared_ptr<circuit> temp_branch(new series(build_series(frequency, phase)));
        parallel_vector.push_back(std::move(temp_branch));
    }
    return parallel_vector;
}

std::vector<std::shared_ptr<circuit>> nested_parallel(double frequency, double phase, int no_of_branches)
{
    // vector of base class shared pointers to store constructed objects in this nested parallel part
    std::vector<std::shared_ptr<circuit>> nested_parallel_vector;
    for (int i{}; i < no_of_branches; i++)
    {
        std::vector<std::shared_ptr<circuit>> temp;
        std::string serial_comp{};
        std::string parallel_comp{};
        std::cout << "For branch " << i + 1 << ":" << std::endl;

        std::cout << "Enter 'Y' or 'y' if this branch has a serial component" << std::endl;
        std::cin >> serial_comp;
        if (serial_comp == "Y" || serial_comp == "y")
        {
            std::cout << "Building the serial part" << std::endl;
            std::shared_ptr<circuit> temp_serial(new series(build_series(frequency, phase)));
            temp.push_back(std::move(temp_serial));
        }
        std::cin.clear();
        std::cin.ignore();

        std::cout << "Enter 'Y' or 'y' if this branch has a parallel component" << std::endl;
        std::cin >> parallel_comp;
        if (parallel_comp == "Y" || parallel_comp == "y")
        {
            std::cout << "Enter the number of branches in this parallel component: " << std::endl;
            int temp_no_of_branches;
            std::cin >> temp_no_of_branches;
            std::shared_ptr<circuit> temp_parallel(new parallel(nested_parallel(frequency, phase, temp_no_of_branches)));
            temp.push_back(std::move(temp_parallel));
        }
        std::cin.clear();
        std::cin.ignore();
        std::shared_ptr<circuit> branch(new series(temp));
        nested_parallel_vector.push_back(std::move(branch));
    }
    return nested_parallel_vector;
}

void construction()
{
    double supply_frequency, supply_phase, supply_voltage;
    std::cout << "Enter Supply voltage parameters: " << std::endl;
    std::cout << "Supply voltage: " << std::endl;
    std::cin >> supply_voltage;
    if (supply_voltage <= 0)
    {
        std::cin.clear();
        std::cin.ignore();
        do
        {
            std::cout << "Invalid input, try again" << std::endl;
            std::cin >> supply_voltage;
        } while (supply_voltage <= 0);
    }

    std::cout << "Supply voltage frequency: " << std::endl;
    std::cin >> supply_frequency;

    if (supply_frequency <= 0)
    {
        std::cin.clear();
        std::cin.ignore();
        do
        {
            std::cout << "Invalid input, try again" << std::endl;
            std::cin >> supply_frequency;
        } while (supply_frequency <= 0);
    }

    std::cout << "Supply voltage phase: " << std::endl;
    std::cin >> supply_phase;

    int type;
    std::cout << "Please choose your circuit: " << std::endl;
    std::cout << "--------------------------- " << std::endl;
    std::cout << "1: pure serial AC circuit" << std::endl;
    std::cout << "2: pure parallel AC circuit" << std::endl;
    std::cout << "3: hybrid circuit (a pure serial + a pure parallel part)" << std::endl;
    std::cout << "4: nested parallel circuit" << std::endl;
    std::cout << "5: General circuit" << std::endl;
    std::cout << "Entering anything else will halt the programme" << std::endl;
    std::cin >> type;

    std::vector<circuit *> constructed_circuit;
    if (type == 1)
    {
        // pure series
        std::cout << "Building the series circuit..." << std::endl;
        series pure_series = series(build_series(supply_frequency, supply_phase));
        constructed_circuit.push_back(&pure_series);
        circuit series_circuit = circuit(constructed_circuit, supply_voltage);
        series_circuit.print(1);
    }
    else if (type == 2)
    {
        // pure parallel
        std::cout << "Building a parallel circuit..." << std::endl;
        std::cout << "Enter the number of branches in this part: " << std::endl;
        int no_of_branches;
        std::cin >> no_of_branches;
        parallel pure_parallel = parallel(build_parallel(supply_frequency, supply_phase, no_of_branches));
        constructed_circuit.push_back(&pure_parallel);
        circuit parallel_circuit = circuit(constructed_circuit, supply_voltage);
        parallel_circuit.print(2);
    }
    else if (type == 3)
    {
        // hybrid
        int no_of_branches;
        std::cout << "Building hybrid circuit ..." << std::endl;
        std::cout << "Building the series part" << std::endl;
        series series_part = series(build_series(supply_frequency, supply_phase));

        std::cout << "Building the parallel part" << std::endl;
        std::cout << "Enter the number of branches in this circuit" << std::endl;
        std::cin >> no_of_branches;

        parallel parallel_part = parallel(build_parallel(supply_frequency, supply_phase, no_of_branches));
        constructed_circuit.push_back(&series_part);
        constructed_circuit.push_back(&parallel_part);
        circuit hybrid_circuit = circuit(constructed_circuit, supply_voltage);
        hybrid_circuit.print(0);
    }
    else if (type == 4)
    {
        // nested parallel
        std::cout << "Building a nested parallel circuit..." << std::endl;
        std::cout << "Enter the number of branches in this part: " << std::endl;
        int no_of_branches;
        std::cin >> no_of_branches;

        parallel nested_parallel_circuit = parallel(nested_parallel(supply_frequency, supply_phase, no_of_branches));
        constructed_circuit.push_back(&nested_parallel_circuit);
        circuit parallel_circuit = circuit(constructed_circuit, supply_voltage);
        parallel_circuit.print(0);
    }
    else if (type == 5)
    {
        // general circuit
        std::vector<std::shared_ptr<circuit>> circuit_5;
        std::string type;
        int no_of_parts;
        std::cout << "Building a general circuit..." << std::endl;
        std::cout << "Enter the number of series or parallel parts in this circuit." << std::endl;
        std::cin >> no_of_parts;

        for (int i{}; i < no_of_parts; i++)
        {
            std::cout << "For part " << i + 1 << ":" << std::endl;
            std::cout << "Enter 's' if this part is connected in series, 'p' if parallel." << std::endl;
            std::cin >> type;
            if (type == "s")
            {
                std::cout << "This part is connected in series" << std::endl;
                std::shared_ptr<circuit> series_part(new series(build_series(supply_frequency,supply_phase)));
                circuit_5.push_back(std::move(series_part));
            }
            else if (type == "p")
            {
                std::cout << "This part is connected in parallel" << std::endl;
                std::cout << "Enter the number of branches in this circuit" << std::endl;
                int no_of_branches;
                std::cin >> no_of_branches;
                std::shared_ptr<circuit> parallel_part(new parallel(nested_parallel(supply_frequency,supply_phase,no_of_branches)));
                circuit_5.push_back(std::move(parallel_part));
            }
            else
            {
                std::cout << "Invalid input, try again" << std::endl;
                i -= 1;
            }
        }
        series connecting_parts = series(circuit_5);
        constructed_circuit.push_back(&connecting_parts);
        circuit general_circuit = circuit(constructed_circuit, supply_voltage);
        general_circuit.print(0);
    }
    else
    {
        std::cout << "Opted out..." << std::endl;
    }
}

int main()
{
    std::cout << "This programme calculates the impedance of an AC circuit." << std::endl;
    std::cout << "Users can create a circuit of arbitary length in series, parallel or nested." << std::endl;
    std::cout << "Programme can prints out constructed pure series or pure parallel circuit." << std::endl;
    std::cout << "Allowed components in this programme: resistor, inductor, capacitor" << std::endl;
    std::cout << std::endl;
    std::cout << "======= Building the circuit =======" << std::endl;
    std::cout << "Input parameters required: Supply Voltage, frequency and phase." << std::endl;
    construction();

    return 0;
}