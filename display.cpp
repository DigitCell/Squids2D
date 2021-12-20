#include "display.hpp"
#include "display.hpp"

Display::Display(uint32_t _win_width ,
                 uint32_t _win_height,
                 float _world_width ,
                 float _world_height):
                win_width(_win_width ),
                win_height(_win_height),
                world_width(_world_width ),
                world_height(_world_height),
                m_window(sf::VideoMode(_win_width, _win_height), "Wood 01", sf::Style::Default),
                //   m_event_manager(m_window),
                m_zoom(1.0f),
                m_offsetX(0.0f),
                m_offsetY(0.0f),
                m_va(sf::Quads, 0)

{

                m_target.create(world_width, world_height);
                settings.antialiasingLevel = 4;
                //m_window.setVerticalSyncEnabled(true);
                m_window.setFramerateLimit(60);

                m_windowOffsetX = m_window.getSize().x * 0.0f;
                m_windowOffsetY = m_window.getSize().y * 0.0f;

                sf::Text text;
                text.setFont(font);
                text.setCharacterSize(5);
                text.setFillColor(sf::Color(150, 150, 150));

                ImGui::SFML::Init(m_window);

                static ImGuiStyle* style = &ImGui::GetStyle();
                style->Alpha = 0.75f;


                for (int i=0; i<1500; i++)
                {
                    int baseColorR=(int)(145*(((float) rand() / (RAND_MAX))));
                    int baseColorG=(int)(145*(((float) rand() / (RAND_MAX))));
                    int baseColorB=(int)(145*(((float) rand() / (RAND_MAX))));

                    color_list.push_back(sf::Color(100+baseColorR,100+baseColorG,100+baseColorB,255));

                }

}

void Display::Clear_window()
{
     m_window.clear();
     m_target.clear(sf::Color::White);
     Draw();
}

void Display::Frame_draw()
{

    m_window.display();
}

bool Display::ProcessEvents()
{
    sf::Event event;
        while (m_window.pollEvent(event)) {
           ImGui::SFML::ProcessEvent(event);

           if (event.type == sf::Event::Closed) {
               ImGui::SFML::Shutdown();
               m_window.close();
               return false;

           }

           if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
               keyLeftPressed=true;
           else
               keyLeftPressed=false;

           if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
               keyRightPressed=true;
           else
               keyRightPressed=false;
        }

        if(m_window.isOpen())
        {

            ImGui::SFML::Update(m_window, deltaClock.restart());

            ImGui::Begin("Particle experiments");
                ImGui::Text("frame rate %f", render_time+solver_time);
                ImGui::Text("frame fps %f", 1000.0f/(render_time+solver_time));

                ImGui::Text("frame graph rate %f", render_time);
                ImGui::Text("frame graph fps %f", render_fps);

                ImGui::Text("frame solver rate %f", solver_time);
                ImGui::Text("frame solver fps %f", solver_fps);


                if (ImGui::Button("Step Graph"))
                {
                   stepGraphPress=true;

                }

                ImGui::Checkbox("Start-Pause generating", &StartPausePhysics);
                ImGui::SliderFloat("Thikness %f", &thickness, 0.5f , 7.0f);


                 ImGui::SliderFloat("Use tree zoom %f", &zoom, 0.05f , 10.0f);
                 ImGui::SliderInt("Use deltaX %d", &deltaX, -4000 , 4000);
                 ImGui::SliderInt("use deltaY %d", &deltaY, -4000 , 4000);
                 ImGui::SliderInt("SeconddeltaX %d", &deltaX2, -1000 , 1000);


            ImGui::End();

            ImGui::Begin("Particle Window");
               m_target_imgui=m_target.getTexture();

               ImGui::Image(m_target_imgui);

            ImGui::End();


            ImGui::EndFrame();
            ImGui::SFML::Render(m_window);
        }

        return true;
}

void Display::Draw()
{
    sf::Clock clock;
    sf::RectangleShape ground(sf::Vector2f(c_world_width, c_world_height));
    ground.setFillColor(sf::Color(25,25,25,255));

    sf::RenderStates rs_ground;
    rs_ground.transform.translate(m_windowOffsetX, m_windowOffsetY);
    rs_ground.transform.scale(m_zoom, m_zoom);
    rs_ground.transform.translate(-m_offsetX, -m_offsetY);

    m_target.draw(ground, rs_ground);

    sf::CircleShape circle;
    circle.setRadius(2.0f);


    sf::Transform transform;
    transform.scale(sf::Vector2f(zoom,zoom));
    transform.translate(sf::Vector2f(deltaX+c_world_width/2.0f,deltaY+c_world_height/2.0f));
    {
        circle.setPosition(-circle.getRadius(), -circle.getRadius());
        circle.setFillColor(sf::Color::White);
        m_target.draw(circle,transform);
    }
    {
        circle.setPosition(100-circle.getRadius(), -circle.getRadius());
        circle.setFillColor(sf::Color::Green);
        m_target.draw(circle,transform);
    }
    {
        circle.setPosition(-circle.getRadius(), 100 -circle.getRadius());
        circle.setFillColor(sf::Color::Blue);
        m_target.draw(circle,transform);
    }

    render_time = clock.getElapsedTime().asMicroseconds() * 0.001f;
    render_fps = 1000.0f/render_time;

}

void Display::DrawCephalopods(Agent& agent)
{

    sf::CircleShape circle;
    circle.setRadius(2.0f);

    int count_nodes=0;
    float zoom2=1.0f;


    {
        circle.setFillColor(color_list[agent.index]);
        circle.setRadius(agent.body.radius);

        circle.setPosition(zoom2*static_cast<float>(agent.position.x)-circle.getRadius(),zoom2*static_cast<float>(agent.position.y)-circle.getRadius());

        sf::Transform transform;
        transform.scale(sf::Vector2f(zoom,zoom));
        transform.translate(sf::Vector2f(deltaX+c_world_width/2.0f,deltaY+c_world_height/2.0f));

        m_target.draw(circle, transform);
        count_nodes++;
    }



    for(auto appendage:agent.body.appendages)
    {
        for(auto node:appendage.segments)
        {

            {
                circle.setFillColor(color_list[agent.index]);
                circle.setRadius(4.0f);

                float x = node.positionPrevious.x + (node.position.x - node.positionPrevious.x);
                float y = node.positionPrevious.y + (node.position.y - node.positionPrevious.y);

                circle.setPosition(zoom2*static_cast<float>(x)-circle.getRadius(),zoom2*static_cast<float>(y)-circle.getRadius());

                sf::Transform transform;
                transform.scale(sf::Vector2f(zoom,zoom));
                transform.translate(sf::Vector2f(deltaX+c_world_width/2.0f,deltaY+c_world_height/2.0f));

                m_target.draw(circle, transform);
                count_nodes++;
            }
        }
    }
}

void Display::DrawCephalopodsSpline(Agent &agent)
{

    sf::CircleShape circle;
    circle.setRadius(2.0f);

    int count_nodes=0;
    float zoom2=1.0f;

    float thiknessTentacle=15.5f;
    float radiusHead=2.5f;

    {
        circle.setFillColor(color_list[agent.index]);
        circle.setRadius(radiusHead*agent.body.radius);

        circle.setPosition(zoom2*static_cast<float>(agent.position.x)-circle.getRadius(),zoom2*static_cast<float>(agent.position.y)-circle.getRadius());

        sf::Transform transform;
        transform.scale(sf::Vector2f(zoom,zoom));
        transform.translate(sf::Vector2f(deltaX+c_world_width/2.0f,deltaY+c_world_height/2.0f));

        m_target.draw(circle, transform);
        count_nodes++;
    }




    for(auto appendage:agent.body.appendages)
    {
        std::vector<Vector2> splinePoints;

        {
            Vector2 vtempA=Vector2(agent.position.x,agent.position.y);
            splinePoints.push_back(vtempA);
            Vector2 vtemp2A=Vector2(appendage.segments[0].position.x,appendage.segments[0].position.y);
            splinePoints.push_back(vtemp2A);
            Vector2 vtemp2AA=Vector2(appendage.segments[1].position.x,appendage.segments[1].position.y);

        }

        for(int i=1; i<appendage.segments.size()-1;i++)
        {
            cpVect a1=cpv(appendage.segments[i].position.x,appendage.segments[i].position.y);
            cpVect a2=cpv(appendage.segments[i+1].position.x,appendage.segments[i+1].position.y);
            cpVect deltaNorm=cpvnormalize(cpvsub(a1,a2));

            cpVect  deltaPerpedicular=cpv(-deltaNorm.y,deltaNorm.x);



            float thickness=thiknessTentacle-i*0.55f-0.35f*i*cos(i*2.0f/M_PI);
            if(thickness<0)
                thickness=0.0f;

            if(i<2)
                thickness*=2.0f;

            cpVect p1=cpvadd(a1,cpvmult( deltaPerpedicular,thickness));

            Vector2 vtemp=Vector2(p1.x,p1.y);

            splinePoints.push_back(vtemp);
        }
        {

         Vector2 vtemp=Vector2(appendage.segments.back().position.x,appendage.segments.back().position.y);
         splinePoints.push_back(vtemp);

        }

        for(int i=appendage.segments.size()-1; i>0;i--)
        {
            cpVect a1=cpv(appendage.segments[i].position.x,appendage.segments[i].position.y);
            cpVect a2=cpv(appendage.segments[i-1].position.x,appendage.segments[i-1].position.y);
            cpVect deltaNorm=cpvnormalize(cpvsub(a1,a2));

            cpVect  deltaPerpedicular=cpv(-deltaNorm.y,deltaNorm.x);
            float thickness=thiknessTentacle-i*0.55f-(appendage.segments.size()-i)*cos((appendage.segments.size()-i)*2.0f/M_PI)*0.15f;
            if(thickness<0)
                thickness=0.0f;
            if(i<3)
                thickness*=2.0f;

            cpVect p1=cpvadd(a2,cpvmult( deltaPerpedicular,thickness));

            Vector2 vtemp=Vector2(p1.x,p1.y);

            splinePoints.push_back(vtemp);
        }

        {

            Vector2 vtemp2A=Vector2(appendage.segments[0].position.x,appendage.segments[0].position.y);
            splinePoints.push_back(vtemp2A);

            Vector2 vtempA=Vector2(agent.position.x+0.1,agent.position.y);
            splinePoints.push_back(vtempA);

        }

         UniformCRSpline<Vector2> s(splinePoints);

         //draw the spline
         float stepSize = 0.75f;
         float currentStep =stepSize;
         float limit = s.getMaxT()+ 0.01f;

         while(currentStep <= limit)
         {
             drawSplineSegmentDerivative(s,currentStep - stepSize, currentStep, agent.index);
             currentStep += stepSize;
         }


        for(int i=0; i<appendage.segments.size();i++)
        {

            Segment node=appendage.segments[i];
            {
                circle.setFillColor(color_list[agent.index]);
                circle.setRadius(2.0f);

                float x = node.positionPrevious.x + (node.position.x - node.positionPrevious.x);
                float y = node.positionPrevious.y + (node.position.y - node.positionPrevious.y);

                circle.setPosition(zoom2*static_cast<float>(x)-circle.getRadius(),zoom2*static_cast<float>(y)-circle.getRadius());

                sf::Transform transform;
                transform.scale(sf::Vector2f(zoom,zoom));
                transform.translate(sf::Vector2f(deltaX+c_world_width/2.0f,deltaY+c_world_height/2.0f));

                m_target.draw(circle, transform);
                count_nodes++;
            }
        }

       {
           circle.setFillColor(sf::Color(25,25,25,255));
           circle.setRadius((radiusHead-0.5f)*agent.body.radius);

           circle.setPosition(zoom2*static_cast<float>(agent.position.x)-circle.getRadius(),zoom2*static_cast<float>(agent.position.y)-circle.getRadius());

           sf::Transform transform;
           transform.scale(sf::Vector2f(zoom,zoom));
           transform.translate(sf::Vector2f(deltaX+c_world_width/2.0f,deltaY+c_world_height/2.0f));

           m_target.draw(circle, transform);
           count_nodes++;
       }

    }

}

void Display::DrawBrain(Agent &agent)
{


    sf::CircleShape circle;
    circle.setRadius(5.0f);

    int count_nodes=0;
    float zoom2=1.0f;

    int numberNeurons=agent.body.brain.neurons.size();
    float sectorStep=2*M_PI/numberNeurons;
    float anglePos=cpvtoangle(agent.direction);
    for(auto neuron:agent.body.brain.neurons)
    {

        cpVect neuronPosition=cpvadd(agent.position,cpvmult(cpvforangle(anglePos), agent.body.radius));
        anglePos+=sectorStep;


        float thiknessTentacle=15.5f;
        float radiusHead=6.5f;

        {
            sf::Color tempColor;
            if(neuron.output>0)
                tempColor=sf::Color(75,255*neuron.output/0.5f,75,255);
            else
                tempColor=sf::Color(255*neuron.output/0.5f,75,75,255);

            circle.setFillColor(tempColor);
            circle.setRadius(radiusHead);

            circle.setPosition(zoom2*static_cast<float>(neuronPosition.x)-circle.getRadius(),zoom2*static_cast<float>(neuronPosition.y)-circle.getRadius());

            sf::Transform transform;
            //transform.rotate(cpvtoangle(agent.direction));
            transform.scale(sf::Vector2f(zoom,zoom));
            transform.translate(sf::Vector2f(deltaX+c_world_width/2.0f,deltaY+c_world_height/2.0f));

            m_target.draw(circle, transform);
            count_nodes++;
        }

    }


}


void  Display::drawSplineSegmentDerivative(const Spline<Vector2> &s, float beginT, float endT, int color)
{
    auto beginData = s.getPosition(beginT);
    auto endData = s.getPosition(endT);

    float middleT = (beginT + endT) * .5;

    auto midExpected =  (beginData + endData) * .5f;
    auto midActual = s.getPosition((beginT + endT) * .5f);
    float minDelta = .15f;
    float maxDistance = 0.7f;
    if((endT - beginT) > minDelta)

    {

        if((midExpected - midActual).lengthSquared() > maxDistance)
        {
            drawSplineSegmentDerivative(s, beginT, middleT, color);
            drawSplineSegmentDerivative(s, middleT, endT, color);
        }
        else

        {
            sf::Vertex line[2];

            line[0].position.x = beginData[0];
            line[0].position.y = beginData[1];
            line[1].position.x = endData[0];
            line[1].position.y = endData[1];

            line[0].color=color_list[color];
            line[1].color=color_list[color];

            sf::Transform transform;
            transform.scale(sf::Vector2f(zoom,zoom));
            transform.translate(sf::Vector2f(deltaX+c_world_width/2.0f,deltaY+c_world_height/2.0f));

            m_target.draw(line, 2, sf::Lines,transform);

        }
    }
}

void Display::DrawCephalopodsSplineFill(Agent &agent)
{

    sf::CircleShape circle;
    circle.setRadius(2.0f);

    int count_nodes=0;
    float zoom2=1.0f;

    float thiknessTentacle=15.5f;
    float radiusHead=2.5f;

    {
        circle.setFillColor(color_list[agent.index]);
        circle.setRadius(radiusHead*agent.body.radius);

        circle.setPosition(zoom2*static_cast<float>(agent.position.x)-circle.getRadius(),zoom2*static_cast<float>(agent.position.y)-circle.getRadius());

        sf::Transform transform;
        transform.scale(sf::Vector2f(zoom,zoom));
        transform.translate(sf::Vector2f(deltaX+c_world_width/2.0f,deltaY+c_world_height/2.0f));

        m_target.draw(circle, transform);
        count_nodes++;
    }




    for(auto appendage:agent.body.appendages)
    {
        std::vector<Vector2> splinePointsL;
        {

            {
                Vector2 vtempA=Vector2(agent.position.x,agent.position.y);
                splinePointsL.push_back(vtempA);
                Vector2 vtemp2A=Vector2(appendage.segments[0].position.x,appendage.segments[0].position.y);
                splinePointsL.push_back(vtemp2A);
                Vector2 vtemp2AA=Vector2(appendage.segments[1].position.x,appendage.segments[1].position.y);
            }

            for(int i=1; i<appendage.segments.size()-1;i++)
            {
                cpVect a1=cpv(appendage.segments[i].position.x,appendage.segments[i].position.y);
                cpVect a2=cpv(appendage.segments[i+1].position.x,appendage.segments[i+1].position.y);
                cpVect deltaNorm=cpvnormalize(cpvsub(a1,a2));

                cpVect  deltaPerpedicular=cpv(-deltaNorm.y,deltaNorm.x);

                float thickness=thiknessTentacle-i*0.55f;
                if(thickness<0)
                    thickness=0.0f;

                if(i<2)
                    thickness*=2.0f;

                cpVect p1=cpvadd(a1,cpvmult( deltaPerpedicular,thickness));

                Vector2 vtemp=Vector2(p1.x,p1.y);

                splinePointsL.push_back(vtemp);
            }
        }
        UniformCRSpline<Vector2> sL(splinePointsL);

        std::vector<Vector2> splinePointsR;
        {
            {
                Vector2 vtempA=Vector2(agent.position.x,agent.position.y);
                splinePointsR.push_back(vtempA);
                Vector2 vtemp2A=Vector2(appendage.segments[0].position.x,appendage.segments[0].position.y);
                splinePointsR.push_back(vtemp2A);
                Vector2 vtemp2AA=Vector2(appendage.segments[1].position.x,appendage.segments[1].position.y);
            }

            for(int i=1; i<appendage.segments.size()-1;i++)
            {
                cpVect a1=cpv(appendage.segments[i].position.x,appendage.segments[i].position.y);
                cpVect a2=cpv(appendage.segments[i+1].position.x,appendage.segments[i+1].position.y);
                cpVect deltaNorm=cpvnormalize(cpvsub(a1,a2));

                cpVect  deltaPerpedicular=cpv(-deltaNorm.y,deltaNorm.x);

                float thickness=thiknessTentacle-i*0.55f;
                if(thickness<0)
                    thickness=0.0f;

                if(i<2)
                    thickness*=2.0f;

                cpVect p1=cpvadd(a1,cpvmult( cpvneg(deltaPerpedicular),thickness));

                Vector2 vtemp=Vector2(p1.x,p1.y);

                splinePointsR.push_back(vtemp);
            }

        }
        UniformCRSpline<Vector2> sR(splinePointsR);

        //draw the spline
        float stepSize = 0.75f;
        float currentStep =stepSize;
        float limit = sL.getMaxT()+ 0.01f;

        vector<sf::Vector2f> pointForDraw;
        vector<sf::Vector2f> pointForDrawL;
        vector<sf::Vector2f> pointForDrawR;

        while(currentStep <= limit)
        {
            auto beginDataL = sL.getPosition(currentStep - stepSize);
            auto endDataL =   sL.getPosition(currentStep);

            auto beginDataR = sR.getPosition(currentStep - stepSize);
            auto endDataR =   sR.getPosition(currentStep);


            pointForDrawR.push_back(sf::Vector2f(beginDataR[0],beginDataR[1]));
            pointForDrawL.push_back(sf::Vector2f(beginDataL[0],beginDataL[1]));

            pointForDrawR.push_back(sf::Vector2f(endDataR[0],endDataR[1]));
            pointForDrawL.push_back(sf::Vector2f(endDataL[0],endDataL[1]));

            pointForDraw.push_back(sf::Vector2f(beginDataR[0],beginDataR[1]));
            pointForDraw.push_back(sf::Vector2f(beginDataL[0],beginDataL[1]));

            pointForDraw.push_back(sf::Vector2f(endDataR[0],endDataR[1]));
            pointForDraw.push_back(sf::Vector2f(endDataL[0],endDataL[1]));

            currentStep += stepSize;
        }

        int deltaTriangle=70;
        int deltaPointsLine=pointForDraw.size()-2*deltaTriangle;

        int deltaPoints=deltaPointsLine;
        if(deltaPoints<=0)
            deltaPoints=pointForDraw.size();
        else
            deltaPoints=2*deltaTriangle;

        {
            sf::VertexArray va(sf::TriangleStrip, deltaPoints);
            for(int i=0; i< deltaPoints;i++)
            {
              va[i] = pointForDraw[i];
            }

            sf::Transform transform;
            transform.scale(sf::Vector2f(zoom,zoom));
            transform.translate(sf::Vector2f(deltaX+c_world_width/2.0f,deltaY+c_world_height/2.0f));

            sf::Color tempColor=color_list[agent.index];
            int n=4;
            float colorCounterR=tempColor.r;
            float colorCounterG=tempColor.g;
            float colorCounterB=tempColor.b;

            float colorCounterRd=255-colorCounterR;
            float colorCounterGd=255-colorCounterG;
            float colorCounterBd=255-colorCounterB;

            colorCounterRd/=(2*deltaPoints/(n));
            colorCounterGd/=(2*deltaPoints/(n));
            colorCounterBd/=(2*deltaPoints/(n));



            for(int i=0; i< deltaPoints;i++)
            {
               if(i%n==0)
               {

               colorCounterR+=colorCounterRd;
               colorCounterG+=colorCounterGd;
               colorCounterB+=colorCounterBd;

                tempColor.r=colorCounterR;
                if(tempColor.r>255)
                    tempColor.r=255;

                tempColor.g=colorCounterG;
                if(tempColor.g>255)
                    tempColor.g=255;

                tempColor.b=colorCounterB;
                if(tempColor.b>255)
                    tempColor.b=255;
               }

                va[i].color=tempColor;
            }

             m_target.draw(va,transform);
        }

        if( deltaPoints!=pointForDraw.size())
        {
            deltaPointsLine/=2;
            sf::VertexArray va(sf::Lines, deltaPointsLine-2);
            for(int i=0; i< deltaPointsLine-2;i++)
            {
              va[i] = pointForDrawL[i+deltaTriangle];
            }

            sf::Transform transform;
            transform.scale(sf::Vector2f(zoom,zoom));
            transform.translate(sf::Vector2f(deltaX+c_world_width/2.0f,deltaY+c_world_height/2.0f));

            sf::Color tempColor=color_list[agent.index];
            int n=4;
            float colorCounterR=tempColor.r;
            float colorCounterG=tempColor.g;
            float colorCounterB=tempColor.b;

            float colorCounterRd=255-colorCounterR;
            float colorCounterGd=255-colorCounterG;
            float colorCounterBd=255-colorCounterB;

            colorCounterRd/=(2*deltaPoints/(n));
            colorCounterGd/=(2*deltaPoints/(n));
            colorCounterBd/=(2*deltaPoints/(n));

            for(int i=0; i<  deltaPointsLine-2;i++)
            {
               if(i%n==0)
               {

               colorCounterR+=colorCounterRd;
               colorCounterG+=colorCounterGd;
               colorCounterB+=colorCounterBd;

                tempColor.r=colorCounterR;
                if(tempColor.r>255)
                    tempColor.r=255;

                tempColor.g=colorCounterG;
                if(tempColor.g>255)
                    tempColor.g=255;

                tempColor.b=colorCounterB;
                if(tempColor.b>255)
                    tempColor.b=255;


               }
                va[i].color=tempColor;
            }
             m_target.draw(va,transform);
        }

           {
               circle.setFillColor(sf::Color(25,25,25,255));
               circle.setRadius((radiusHead-0.5f)*agent.body.radius);

               circle.setPosition(zoom2*static_cast<float>(agent.position.x)-circle.getRadius(),zoom2*static_cast<float>(agent.position.y)-circle.getRadius());

               sf::Transform transform;
               transform.scale(sf::Vector2f(zoom,zoom));
               transform.translate(sf::Vector2f(deltaX+c_world_width/2.0f,deltaY+c_world_height/2.0f));

               m_target.draw(circle, transform);
               count_nodes++;
           }
    }

}


