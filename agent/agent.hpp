#ifndef AGENT_HPP
#define AGENT_HPP


#include "../constants.hpp"
#include "dna/dnabody.hpp"
#include "dna/dna.hpp"
#include "../math/cpVect.h"
#include "brain/brain.hpp"
#include "tentacle/tentacle.hpp"
#include "body.hpp"
#include <memory>


class Agent
{
public:
        Agent(
                int _index,
                DNA _dna,
                cpVect _position,
                cpVect _direction):
                index(_index),
                dna(_dna),
                position(_position),
                positionPrevious(_position),
                direction(_direction),
                directionPrevious(_direction),
                body(dna.body,position, positionPrevious, direction,directionPrevious)
        {
           mass=body.getMass();
        }

    DNA dna;
    cpVect position;
    cpVect positionPrevious;
    cpVect direction;
    cpVect directionPrevious;
    cpVect velocity;
    Body body;
    cpVect impulse;
    float mass;
    int eaten = 0;
    int index=0;

    void update()
    {

        positionPrevious=position;
        directionPrevious=direction;

        velocity=cpvmult(velocity, AgentFRICTION);
        position=cpvadd(position,velocity);

        impulse=cpvzero;
        body.update(impulse, position, direction);

        velocity=cpvadd(velocity,cpvmult(impulse,(AgentIMPULSE /mass)));
        direction=cpvsub(direction,cpvmult(impulse,( AgentTORQUE  /mass)));
        direction=cpvnormalize(direction);

    }



};

#endif // AGENT_HPP
