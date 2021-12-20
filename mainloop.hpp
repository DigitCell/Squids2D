#ifndef MAINLOOP_HPP
#define MAINLOOP_HPP

#include "constants.hpp"
#include "display.hpp"
#include "environment.hpp"



class MainLoop
{
public:
    MainLoop();

    Display display;

    void Run();
    void InitGraphs(int numberGraph);

    Environment env;

    int RandomInt(int min, int max)
    {
        return std::rand()%((max - min) + 1) + min;
    }


};

#endif // MAINLOOP_HPP
