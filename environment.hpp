#ifndef ENVIRONMENT_HPP
#define ENVIRONMENT_HPP


#include "constants.hpp"
#include "math/cpVect.h"
#include <memory>
#include "agent/agent.hpp"
#include "agent/dna/dna.hpp"
#include "vector"
#include "iostream"

using namespace std;



class Environment
{
public:
    Environment(
               float _radius
            ):
        radius(_radius),
        agentCount(EnvironmentDEFAULT_AGENT_COUNT)
    {

        initialize(agentCount);

    };

    float radius;
    int agentCount;
    vector<Agent> agents;

    cpVect getInitialPosition(int index) {
        return cpvmult(cpvforangle(index * M_PI * 2.0f / agentCount + M_PI), radius * (1.0f - EnvironmentSPAWN_INSET));
    };

    cpVect getInitialDirection(int index) {
        return cpvforangle(index * M_PI * 2.0f/ agentCount);
    };


    bool initialize(int count)
    {
        for (int agent = 0; agent < count; ++agent)
        {
             agents.push_back( Agent(agent, DNA(), getInitialPosition(agent), getInitialDirection(agent)));
        }
        std::cout<<"Done";
        return true;


    }

};

#endif // ENVIRONMENT_HPP


