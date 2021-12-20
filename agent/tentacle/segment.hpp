#ifndef SEGMENT_HPP
#define SEGMENT_HPP

#include "../../constants.hpp"
#include "../../math/cpVect.h"
#include <memory>
#include <vector>


class Segment
{
public:

    Segment( cpVect _position,
             float _spring =0,
             float _spacing =0
            ):
            position(_position),
            positionPrevious(_position),
            spring(_spring),
            spacing(_spacing)
    {
        parentFlag=true;
    };

    Segment(
                int _index,
                cpVect _position,
                float _spring,
                float _spacing,
                Segment& parent,
                int _parentIndex
            ):
        index(_index),
        position(_position),
        positionPrevious(_position),
        spring(_spring),
        spacing(_spacing),
        parentIndex(_parentIndex)
    {

        parentFlag=false;
        direction =cpvnormalize( cpvsub(parent.position,position));
    };

    int index=0;
    cpVect position;
    cpVect positionPrevious;
    float spring =0;
    float spacing =0;

    cpVect direction;
    cpVect directionPrevious;

    bool parentFlag=false;

    int parentIndex;
    cpVect  delta;


    template <typename T> int sign(T val) {
        return (T(0) < val) - (val < T(0));
    }

    bool update(cpVect& velocity, std::vector<Segment>& parents)
    {

        if(parentFlag)
            return false;

         positionPrevious=position;
         directionPrevious=direction;

         Segment& parent=parents[parentIndex];
         parent.update(velocity, parents);

         direction=cpvnormalize(cpvsub(parent.position,position));
         delta=cpvneg(direction);

         float lateralDot = (direction.x * parent.direction.y - direction.y * parent.direction.x);

         if (cpvdot(direction,parent.direction) < 0) {
                 float force = spring * sign(lateralDot);

                 delta.x += direction.y * force;
                 delta.y -= direction.x * force;
         }
         else {
                 float force = spring * lateralDot;

                 delta.x += direction.y * force;
                 delta.y -= direction.x * force;
         }

         if ((delta.x==0) and (delta.y==0)) {
                 position.x = parent.position.x + spacing;
                 position.y = 0;
         }
         else
             position=cpvadd(parent.position,cpvmult(delta,(spacing/cpvlength(delta))));


        float dx = position.x - positionPrevious.x;
        float dy = position.y - positionPrevious.y;
        float push = (direction.y * dx - direction.x * dy) * pow(abs(lateralDot), SegmentPUSH_POWER);

        velocity.x -= direction.y * push;
        velocity.y += direction.x * push;


         return true;

    }

    void setAnchor(cpVect _position, cpVect _offset, float angle)
    {
        positionPrevious=position;
        directionPrevious=direction;

        position=_position;
        position=cpvadd(position,_offset);
        direction=cpvforangle(angle);
    }


};

#endif // SEGMENT_HPP
