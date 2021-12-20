#include "mainloop.hpp"

MainLoop::MainLoop():
    display(c_window_width, c_window_height, c_world_width, c_world_height),
    env(120.0f)

{
    std::cout<<"Done";
    std::srand(45073);

}


void MainLoop::Run()
{
    sf::Clock deltaClock;

    bool openWindow=true;

    int tickCount=0;
    while (openWindow)
    {
        display.Clear_window();
        deltaClock.restart();

        sf::Clock clock;

        if(openWindow)
        {
            display.solver_time = clock.getElapsedTime().asMicroseconds() * 0.001f;
            display.solver_fps= 1000.0f/display.solver_time;

            int colorCount=0;
            for(auto& agent:env.agents)
            {
               display.DrawCephalopodsSplineFill(agent);
               display.DrawBrain(agent);
               colorCount++;
            }

            for(auto& agent:env.agents)
            {
               agent.update();
            }

            openWindow=display.ProcessEvents();
            display.Frame_draw();

        }

    }

}
