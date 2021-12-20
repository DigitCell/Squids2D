#ifndef BODY_HPP
#define BODY_HPP

#include "../constants.hpp"
#include "dna/dnabody.hpp"
#include "../math/cpVect.h"
#include "brain/brain.hpp"
#include "tentacle/tentacle.hpp"
#include <memory>


class Body
{
public:
    Body(DNAbody _dna, cpVect _position, cpVect _positionPrevious, cpVect _direction, cpVect _directionPrevious):
        dna(_dna),
        position(_position),
        positionPrevious(_positionPrevious),
        direction(_direction),
        directionPrevious(_directionPrevious),
        brain(_dna.brain),
        radius(_dna.radius)


    {
       // brain=std::make_unique<Brain>(_dna.brain);


        for (int appendage = 0; appendage < dna.appendages.size(); ++appendage)
        {
             // switch (dna->appendages[appendage].object) {
             //     case DNATentacle:
             appendages.push_back(Tentacle(
                                              dna.appendages[appendage],
                                              position,
                                              direction,
                                              radius));

             appendages.push_back(Tentacle(
                                              dna.appendages[appendage],
                                              position,
                                              direction,
                                              radius, true));

        }

               //       break;
            //  }

    };

    cpVect position;
    cpVect positionPrevious;
    cpVect direction;
    cpVect directionPrevious;
    float radius;

    vector<Tentacle> appendages;
    Brain brain;
  // std::unique_ptr<Brain> brain;
    DNAbody dna;
 //   std::unique_ptr<DNAbody> dna;

    void update(cpVect& impulse, cpVect pos,cpVect direction)
    {
       brain.update();


       int input = 0;
       int output = 0;

        for (auto& tentacle :appendages) {
            for (int i = 0; i < tentacle.appendage.inputs; ++i)
            {
                tentacle.appendage.position=pos;
                tentacle.appendage.direction=direction;
                tentacle.setInput(brain.outputs[output++].output);
            }//, i);

           // for (int i = 0; i < appendage.appendage.outputs; ++i)
           //     brain->inputs[input++].activation += appendage.getOutput(i);

            tentacle.update(impulse);
        }
    }

    float getMass()
    {
        float appendagesMass = 0;

        for (auto& appendage :appendages)
            appendagesMass += appendage.getMass();

        return M_PI* radius * radius * BodyMASS_PER_AREA + appendagesMass;
    }


};

#endif // BODY_HPP
