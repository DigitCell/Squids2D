#ifndef DNABODY_HPP
#define DNABODY_HPP

#include "../../constants.hpp"
#include "dnatentacle.hpp"
#include "vector"
#include "dnabrain.hpp"

using namespace std;

class DNAbody
{
public:
    DNAbody(float _radius=BodyRADIUS_MIN):
        radius(_radius)
    {

      int amountTentacle=RandomInt(1,3);
      float angle=M_PI/2.0f;
      for(int i=0;i<amountTentacle;i++)
      {
        appendages.push_back(DNATentacle(angle));
        angle+=M_PI/2*amountTentacle;
      }
    };

    DNAbody(float _radius,
            vector<DNATentacle> _appendages,
            DNABrain _brain):
        radius(_radius),
        appendages(_appendages),
        brain(_brain)
    {
    };

    float radius;
    vector<DNATentacle> appendages;
    DNABrain brain;

    DNAbody copy()
    {
       return DNAbody(this->radius, this->appendages, this->brain);

    }

    int RandomInt(int min, int max)
    {
       return std::rand()%((max - min) + 1) + min;
    }


};

#endif // DNABODY_HPP
