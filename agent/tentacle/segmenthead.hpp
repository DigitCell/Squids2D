#ifndef SEGMENTHEAD_HPP
#define SEGMENTHEAD_HPP

#include "../../constants.hpp"
#include "../../math/cpVect.h"
#include "segment.hpp"
#include <memory>

class SegmentHead: public Segment
{
public:
    SegmentHead(cpVect _position):
      Segment(_position)
    {

    };

   void setAnchor(cpVect _position, cpVect _offset, float angle)
   {
       positionPrevious=position;
       directionPrevious=direction;

       position=_position;
       position=cpvadd(position,_offset);
       direction=cpvforangle(angle);
   }


};

#endif // SEGMENTHEAD_HPP
