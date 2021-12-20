#ifndef DISPLAY_HPP
#define DISPLAY_HPP


#pragma once

#include <SFML/Graphics.hpp>

#include <imgui.h>
#include <imgui_internal.h>
#include <imgui-SFML.h>
#include "constants.hpp"
#include "math/cpVect.h"

#include <memory>
#include "agent/agent.hpp"
#include "agent/dna/dna.hpp"
#include "vector"

#include "spline_library/spline.h"
#include "spline_library/splines/uniform_cr_spline.h"
#include "spline_library/splines/natural_spline.h"
#include "spline_library/splines/cubic_hermite_spline.h"
#include "spline_library/splines/quintic_hermite_spline.h"
#include "spline_library/splines/uniform_cubic_bspline.h"
#include "spline_library/vector.h"



class Display
{
public:
    Display(const uint32_t _win_width ,
            const uint32_t _win_height,
            const float _world_width ,
            const float _world_heigh);

    //offset mutators
    void setOffset(float x, float y)  {m_offsetX=x; m_offsetY=y;};
    void setOffset(const sf::Vector2i& off) {m_offsetX=off.x; m_offsetY=off.y;};

    sf::RenderTexture m_target;
    sf::Texture m_target_imgui;

    const uint32_t win_width = 1600;
    const uint32_t win_height = 900;

    const uint32_t world_width = 1600;
    const uint32_t world_height = 900;

    sf::RenderWindow m_window;
    sf::Clock deltaClock;
    float render_time;
    float render_fps;

    float solver_time;
    float solver_fps;

    sf::Font font;

    // sf::RenderTexture render_tex;
    sf::ContextSettings settings;
    sf::VertexArray m_va;

    float m_zoom, m_offsetX, m_offsetY, m_windowOffsetX, m_windowOffsetY;

    void Clear_window();
    void Frame_draw();
    bool ProcessEvents();

    void Draw();

    std::vector<sf::Color> Colors;
    std::vector<sf::Color> color_list;


    //keyboard events

    bool keyLeftPressed=false;
    bool keyRightPressed=false;

    bool recalculateLsystem=false;
    void DrawCephalopods(Agent& agent);
    void DrawCephalopodsSpline(Agent& agent);

    void DrawBrain(Agent& agent);
    bool drawCephalopodsFlag=true;

    bool StartPausePhysics=false;
    bool stepGraphPress=false;

    float thickness=2.5f;

    //Zoom and etc

    float zoom=0.33f;
    int deltaX=700;
    int deltaY=350;
    int deltaX2=0;


    void drawSplineSegmentDerivative(const Spline<Vector2> &s, float beginT, float endT,int color);
    void DrawCephalopodsSplineFill(Agent &agent);
};

#endif // DISPLAY_HPP
