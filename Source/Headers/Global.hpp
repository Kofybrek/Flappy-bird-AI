#pragma once

constexpr float FLAP_SPEED = -4;
constexpr float GRAVITY = 0.25f;

constexpr unsigned char BIRD_SIZE = 16;
constexpr unsigned char BIRD_SPEED = 1;
constexpr unsigned char BIRD_START_X = 37;
constexpr unsigned char FONT_HEIGHT = 32;
constexpr unsigned char GAP_SIZE = 64;
//Minimum indent from the ground and from the top to the gap.
constexpr unsigned char PIPE_INDENT = 32;
//Vertical speed of the pipes.
constexpr unsigned char PIPE_SPEED = 1;
constexpr unsigned char SCREEN_RESIZE = 2;

//We'll generate new pipes after this number of frames.
constexpr unsigned short GENERATOR_TIMER_DURATION = 128;
constexpr unsigned short GROUND_Y = 288;
constexpr unsigned short SCREEN_HEIGHT = 320;
constexpr unsigned short SCREEN_WIDTH = 180;

//-------------------< AI CONSTANTS >-------------------
//(I'm getting too good at writing comments.)

//This means a probability of 1 in 64.
constexpr unsigned char MUTATION_PROBABILITY = 64;
constexpr unsigned char POPULATION_SIZE = 8;
constexpr unsigned char TOTAL_HIDDEN_NODES = 4;
constexpr unsigned char TOTAL_INPUT_NODES = 3;
constexpr unsigned char TOTAL_OUTPUT_NODES = 1;

constexpr std::chrono::microseconds FRAME_DURATION(16667);