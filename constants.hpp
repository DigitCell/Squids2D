#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include <cstdint>
#include "math.h"
#define c_window_width 1900
#define c_window_height 900

#define c_world_width 1400
#define c_world_height 800

#define c_ground_level 50

//DNATentacle
const float DNATentacleDEFAULT_ANGLE = M_PI/2.0f;
const float DNATentacleDEFAULT_LENGTH =55;
const float DNATentacleDEFAULT_SPRING = 0.5;
const float DNATentacleDEFAULT_SPRING_POWER = 3;

//DNABrain
const int DNABrainDEFAULT_INPUTS = 0;
const int DNABrainDEFAULT_OUTPUTS = 2;
const float DNABrainDEFAULT_AXON_CHANCE = .7;

//Body
const float BodyMASS_PER_AREA = .025;
const float BodyNEURONS_PER_AREA = .009; //0.07
const float BodyRADIUS_MIN = 15.5;
const float BodyRADIUS_MAX = 100;

//DNAAxon
const uint32_t DNAAxonINDEX_MASK =  0x0FFFFFFF;
const uint32_t DNAAxonFLAG_INPUT =  0x10000000;
const uint32_t DNAAxonFLAG_NEURON = 0x20000000;
const uint32_t DNAAxonFLAG_OUTPUT = 0x40000000;

//Axon
const float AxonWEIGHT_MIN = -5;
const float AxonWEIGHT_MAX = 5;

//Segment
const float SegmentPUSH_POWER = 2.5; //2.5

//Tentacle
const float TentacleSPACING = 15;
const float TentacleMASS_PER_SEGMENT = 1.5;

//Neuron

const float NeuronDECAY = 0.9; //0.9
const float NeuronACTIVATION_THRESHOLD = .2;

//Agent

const float AgentFRICTION = .88;
const float AgentTORQUE = .8;
const float AgentIMPULSE = 20;

//Environment

const float EnvironmentFRAME_TIME = .065;
const float EnvironmentSPAWN_INSET = .05;
const float EnvironmentDEFAULT_AGENT_COUNT =25;
const float EnvironmentDEFAULT_SIM_TIME = 20;
const float EnvironmentMAX_FRAME_TIME = 1 / 60;
const float EnvironmentWARP_STEP = EnvironmentFRAME_TIME * 10;
const float EnvironmentSELECT_RADIUS_MULTIPLIER = 3;


class Constants
{
public:
    Constants();
};

#endif // CONSTANTS_HPP
