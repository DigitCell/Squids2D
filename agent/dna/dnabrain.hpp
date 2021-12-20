#ifndef DNABRAIN_HPP
#define DNABRAIN_HPP

#include "../../constants.hpp"
#include "dnaaxon.hpp"
#include <vector>
#include "math.h"
#include <random>

using namespace std;

class DNABrain
{
public:

    DNABrain() {
        inputs=DNABrainDEFAULT_INPUTS;
        outputs=DNABrainDEFAULT_OUTPUTS;
        neurons = getAllowedNeurons(BodyRADIUS_MIN);
        axons=makeAxons(neurons,DNABrainDEFAULT_OUTPUTS);
    };

    DNABrain(
            int _inputs,
            int _outputs):
        inputs(_inputs),
        outputs(_outputs)
    {
       neurons = getAllowedNeurons(BodyRADIUS_MIN);
       axons=makeAxons(neurons,DNABrainDEFAULT_OUTPUTS);


    };


    DNABrain(
            int _inputs,
            int _neurons,
            int _outputs,
            vector<DNAAxon> _axons):
        inputs(_inputs),
        neurons(_neurons),
        outputs(_outputs),
        axons(_axons)
    {

    };


    int inputs;
    int neurons;
    int outputs;
    vector<DNAAxon> axons;

    int getAllowedNeurons(float radius)
    {
        return floor(M_PI * radius * radius * BodyNEURONS_PER_AREA);
    };

    vector<DNAAxon> makeAxons(int neuronCount, int outputCount)
    {
        vector<DNAAxon> axons;

            for (int neuron = 0; neuron < neuronCount; ++neuron) {
                for (int other = 0; other < neuronCount; ++other) {
                    if (other == neuron)
                        continue;
                    float r1=RandomFloat();
                    if (r1 > DNABrainDEFAULT_AXON_CHANCE)
                        continue;

                    axons.push_back(DNAAxon(
                        neuron | DNAAxonFLAG_NEURON,
                        other | DNAAxonFLAG_NEURON));
                }

                for (int output = 0; output < outputCount; ++output) {
                    float r1=RandomFloat();
                    if (r1 > DNABrainDEFAULT_AXON_CHANCE)
                        continue;

                    axons.push_back(DNAAxon(
                        neuron | DNAAxonFLAG_NEURON,
                        output | DNAAxonFLAG_OUTPUT));
                }
            }

            return axons;
    }

    DNABrain copy()
    {
        return DNABrain(this->inputs, this->neurons, this->outputs, this->axons);
    }

    int RandomInt(int min, int max)
    {
       return std::rand()%((max - min) + 1) + min;
    }

    float RandomFloat(float M, float N)
    {
       return M + (rand() / ( RAND_MAX / (N-M) ) ) ;
    }

    float RandomFloat()
    {
       return 0.0f+(rand()/(RAND_MAX/1.0f));
    }

};

#endif // DNABRAIN_HPP
