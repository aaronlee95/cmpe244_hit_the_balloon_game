#include "balloons.hpp"

balloons::balloons()
{
    srand(time(0));
    row = 16;
    position = (rand() % 32) + 3;
}

balloons::~balloons(){}

uint8_t balloons::balloonPosition(void)
{
    return position;
}
