#ifndef APPENDAGE_HPP
#define APPENDAGE_HPP

#include "../constants.hpp"
#include "../math/cpVect.h"
#include <memory>
#include "dna/dnatentacle.hpp"
#include "math.h"

class Appendage
{
public:
    Appendage(DNATentacle dna,
              int _inputs,
              int _outputs,
              cpVect _position,
              cpVect _direction,
              float _radius,
              bool flip=false):

        inputs(_inputs),
        outputs(_outputs),
        position(_position),
        direction(_direction)
    {

       if (flip)
           angle= -dna.angle;
       else
           angle = dna.angle;

       offset = cpvmult(cpvforangle(angle),-_radius);

       if(angle==0)
           sign=1;
       else
           sign=signF(angle);

       calculateDelta();

    };


    float angle;
    int inputs;
    int outputs = outputs;
    cpVect offset;
    cpVect position = position;
    cpVect direction = direction;
    int sign = 1;
    cpVect delta;

    float calculateDelta()
    {

        delta.x =offset.x * direction.x - offset.y *direction.y;
        delta.y =offset.x * direction.y + offset.y *direction.x;

        return atan2(-delta.y, -delta.x);

    };

    template <typename T> int signF(T val) {
        return (T(0) < val) - (val < T(0));
    }
};

#endif // APPENDAGE_HPP
