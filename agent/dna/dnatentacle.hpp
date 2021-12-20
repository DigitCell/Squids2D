#ifndef DNATENTACLE_HPP
#define DNATENTACLE_HPP

#include "../../constants.hpp"

class DNATentacle
{
public:
    DNATentacle(float _angle=DNATentacleDEFAULT_ANGLE,
                float _length=DNATentacleDEFAULT_LENGTH,
                float _spring=DNATentacleDEFAULT_SPRING,
                float _springPower=DNATentacleDEFAULT_SPRING_POWER):
                angle(_angle),
                length(_length),
                spring(_spring),
                springPower(_springPower)
    {

    }

    float   angle;
    float   length;
    float   spring;
    float   springPower;

    DNATentacle copy()
    {
        return DNATentacle(this->angle, this->length, this->spring, this->springPower);
    }

};

#endif // DNATENTACLE_HPP
