#ifndef TENTACLE_HPP
#define TENTACLE_HPP


#include "../../constants.hpp"
#include "../../math/cpVect.h"
#include "segment.hpp"
//#include "segmenthead.hpp"
#include <memory>
#include "../dna/dnatentacle.hpp"
#include "../appendage.hpp"
#include "vector"
#include "math.h"

using namespace std;

class Tentacle
{
public:
    Tentacle(DNATentacle dna,
             cpVect position,
             cpVect direction,
             float radius,
             bool flip = false
            ):
        length(dna.length),
        spring(dna.spring),
        springPower(dna.springPower),
        appendage(dna,1,0,position,direction,radius, flip)

    {
        segments.push_back(Segment(cpvadd(position, appendage.delta)));
        segments[0].parentFlag=true;

        buildTail();

    };

    int length;
    float spring;
    float springPower;
    Appendage appendage;
    vector<Segment> segments;

    void setInput(float value)
    {
        float angleTemp=appendage.calculateDelta()+ (2.0f *  value - 1.0f) *  appendage.sign;
        segments[0].setAnchor(appendage.position,appendage.delta, angleTemp);
    };

    void update(cpVect& impulse)
    {
        segments.back().update(impulse, segments);
    };

    int getLength()
    {
        return segments.size();
    };

    float getMass()
    {
        return getLength() * TentacleMASS_PER_SEGMENT;
    };

    void buildTail()
    {
        for (int i = 1; i < length; ++i) {

            float springTemp = spring * pow(1.0f - ((float)(i-1)/ (length - 1)) * 0.35f, springPower);
            auto  tailSegmnet = Segment(i,
                       cpvadd(segments[i-1].position,  cpvmult(cpvnormalize(appendage.delta), TentacleSPACING)), springTemp, TentacleSPACING, segments[i-1], i-1);
            segments.push_back(tailSegmnet);


        }

    };


};

#endif // TENTACLE_HPP
