#ifndef DNA_HPP
#define DNA_HPP

#include "../../constants.hpp"
#include "dnabody.hpp"


class DNA
{
public:
    DNA(){};

    DNA(DNAbody _body)
    {
        body=_body;
    }

    DNAbody body;

    DNA copy()
    {
        return DNA(this->body);
    }
};

#endif // DNA_HPP
