#ifndef DNAAXON_HPP
#define DNAAXON_HPP

#include "../../constants.hpp"
#include <random>

class DNAAxon
{
public:
    DNAAxon( uint32_t _from,
             uint32_t _to):
      from(_from),
      to(_to)
    {
        weight=RandomFloat(AxonWEIGHT_MIN,AxonWEIGHT_MAX);
    };

    DNAAxon( uint32_t _from,
             uint32_t _to,
             float _weight):
      from(_from),
      to(_to),
      weight(_weight)
    {

    };

    uint32_t from;
    uint32_t to;
    float weight;

    DNAAxon copy()
    {
        return DNAAxon(this->to, this->from, this->weight);
    }

    int RandomInt(int min, int max)
    {
       return std::rand()%((max - min) + 1) + min;
    }

    float RandomFloat(float M, float N)
    {
       return M + (rand() / ( RAND_MAX / (N-M) ) ) ;
    }


};

#endif // DNAAXON_HPP
