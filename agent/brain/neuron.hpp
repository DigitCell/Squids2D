#ifndef NEURON_HPP
#define NEURON_HPP

#include "../../constants.hpp"
#include "math.h"

class Neuron
{
public:
    Neuron();

    float activation = .5;
    float output = 0;
    float outputPrevious = 0;

    void update()
    {
        outputPrevious = output;

        float a =activation;

        if (a < -NeuronACTIVATION_THRESHOLD)
            a = a + NeuronACTIVATION_THRESHOLD;
        else if (a > NeuronACTIVATION_THRESHOLD)
            a = a - NeuronACTIVATION_THRESHOLD;
        else
            a = 0.0f;

        output = 1.0f / (1.0f + exp(-a));
        activation *= NeuronDECAY;

    }
};

#endif // NEURON_HPP
