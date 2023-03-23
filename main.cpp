#include <iostream>

#include "neuron.h"

int main(int argc, char **argv)
{
    // OR
    // AND
    // NOR
    // NAND
    // XOR
    const Tornelli::Operation op = Tornelli::Operation::AND;

    Tornelli::Neuron neuron(op);

    for (const Tornelli::Pair &example : Tornelli::examples)
    {
        int x1 = example.first;
        int x2 = example.second;

        std::cout << "Result for " << x1 << " " << Tornelli::opToString(op) << " " << x2 << ": " << neuron.execute(x1, x2) << std::endl;
    }

    std::cout << "Training..." << std::endl;
    neuron.train();

    for (const Tornelli::Pair &example : Tornelli::examples)
    {
        int x1 = example.first;
        int x2 = example.second;

        std::cout << "Result for " << x1 << " " << Tornelli::opToString(op) << " " << x2 << ": " << neuron.execute(x1, x2) << std::endl;
    }

    return 0;
}