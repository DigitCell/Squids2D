#ifndef AXON_HPP
#define AXON_HPP

#include "../../constants.hpp"
#include "../../math/cpVect.h"
#include "../dna/dnaaxon.hpp"
#include "neuron.hpp"

class Axon
{
public:
    Axon(DNAAxon dna, Neuron& _from, Neuron& _to):
        weight(dna.weight),
        from(_from),
        to(_to)
    {};

    float weight;
    Neuron& from;
    Neuron& to;

    void update()
    {
       to.activation +=from.output * weight;
    }
};

#endif // AXON_HPP
