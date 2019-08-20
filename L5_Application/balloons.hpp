#ifndef BALLOONS_HPP_
#define BALLOONS_HPP_

#include <time.h>
#include <stdlib.h>

class balloons
{
public:
    balloons();
    ~balloons();
    uint8_t balloonPosition(void);

private:
    volatile uint8_t row;
    volatile uint8_t position;
};



#endif
