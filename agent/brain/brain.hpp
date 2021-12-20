#ifndef BRAIN_HPP
#define BRAIN_HPP


#include "../../constants.hpp"
#include "../../math/cpVect.h"
#include "../dna/dnaaxon.hpp"
#include "../dna/dnabrain.hpp"

#include "axon.hpp"
#include "neuron.hpp"

#include "memory"
#include <vector>

using namespace  std;


class Brain
{
public:
    Brain(DNABrain _dna):
    dna(_dna)
    {
        for (int input = 0; input < dna.inputs; ++input)
            inputs.push_back(Neuron());

        for (int neuron = 0; neuron < dna.neurons; ++neuron)
            neurons.push_back(Neuron());

        for (int output = 0; output < dna.outputs; ++output)
            outputs.push_back(Neuron());

        for (auto& dnaAxon: dna.axons)
        {
            axons.push_back(Axon(dnaAxon,getNeuron(dnaAxon.from),getNeuron(dnaAxon.to)));
        }

    };


    vector<Neuron> inputs;
    vector<Neuron> neurons;
    vector<Neuron> outputs;
    vector<Axon> axons;
    DNABrain dna;
    //std::unique_ptr<DNABrain> dna;

    Neuron& getNeuron(uint32_t axonIndex)
    {

        switch (axonIndex & ~DNAAxonINDEX_MASK) {
            case DNAAxonFLAG_INPUT:
                return inputs[axonIndex & DNAAxonINDEX_MASK];
            case DNAAxonFLAG_NEURON:
                return neurons[axonIndex & DNAAxonINDEX_MASK];
            case DNAAxonFLAG_OUTPUT:
                return outputs[axonIndex & DNAAxonINDEX_MASK];
        }

    }


    void update()
    {
        for(auto& neuron:neurons)
            neuron.update();

        for(auto& output :outputs)
            output.update();

        for(auto& axon :axons)
            axon.update();

    }

};

#endif // BRAIN_HPP
