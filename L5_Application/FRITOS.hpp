#ifndef FRITOS_HPP_
#define FRITOS_HPP_

#include "tasks.hpp"
#include "LPC17xx.h"
#include "FreeRTOS.h"
#include "stdio.h"
#include <string.h>
#include <LabGPIO.hpp>
#include "acceleration_sensor.hpp"
#include "utilities.h"
#include "arrow.hpp"

extern SemaphoreHandle_t xMutex;

class FRITOS
{
public:
    // Port 2
    enum RGB_PIN
    {
        R1 = 0,
        G1 = 1,
        B1 = 2,
        R2 = 3,
        G2 = 4,
        B2 = 5,
        A = 6,
        B = 7,
        C = 8,
    };
    // Port 0
    enum MATRIX_PIN
    {
        LAT = 1,
        OE = 0,
        CLK = 20,
    };

    bool convert_i = 0;
    bool convert_j = 0;
    int spin = 0;
    FRITOS(bool);
    ~FRITOS();

    void initRGB(void);
    void splashscreen(void);
    void displayObject(arrow &test);
    void enableOE(void);
    void disableOE(void);
    void clockTick(void);
    void latchReset(void);
    void set_row(uint8_t);
    void set_color_top(uint32_t);
    void set_color_bottom(uint32_t);

    volatile uint8_t  m_matrixBuffer[16][32];

    bool m_debug;

private:
    uint8_t dropping = 0;

};

#endif /* FRITOS_HPP_ */
