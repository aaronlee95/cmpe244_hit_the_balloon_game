#include "FRITOS.hpp"

FRITOS::FRITOS (bool debug = false) : m_debug(debug) {}
FRITOS::~FRITOS () {}

void FRITOS::initRGB(void)
{
    if(m_debug) printf("Initializing SJOne...\n");

    // Select GPIO Port 0.0, 0.1 pin-select functionality
    LPC_PINCON->PINSEL0 &= ~(0x4);
    LPC_GPIO0->FIODIR |= (1 << LAT);    // P0.1 -> LAT
    LPC_GPIO0->FIODIR |= (1 << OE);     // P0.0 -> OE
    LPC_GPIO0->FIOSET = (1 << OE);
    LPC_GPIO0->FIOCLR = (1 << LAT);

    // Select GPIO Port 2.0, 2.1, 2.2, 2.3, 2.4, 2.5, 2.6, 2.7, 2.8 pin-select functionality
    LPC_PINCON->PINSEL4 &= ~(0x3FFFF);
    LPC_GPIO2->FIODIR |= (1 << R1);     // P2.0 -> R1
    LPC_GPIO2->FIODIR |= (1 << G1);     // P2.1 -> G1
    LPC_GPIO2->FIODIR |= (1 << B1);     // P2.2 -> B1
    LPC_GPIO2->FIODIR |= (1 << R2);     // P2.3 -> R2
    LPC_GPIO2->FIODIR |= (1 << G2);     // P2.4 -> G2
    LPC_GPIO2->FIODIR |= (1 << B2);     // P2.5 -> B2

    // Select GPIO Port 1.20 pin-select functionality
    LPC_PINCON->PINSEL3 &= ~(3 << 8);
    LPC_GPIO1->FIODIR |= (1 << CLK);      // P1.20 -> CLK
    LPC_GPIO1->FIOCLR = (1 << CLK);

    LPC_GPIO2->FIODIR |= (1 << A);      // P2.6 -> A
    LPC_GPIO2->FIODIR |= (1 << B);      // P2.7 -> B
    LPC_GPIO2->FIODIR |= (1 << C);      // P2.8 -> C
    LPC_GPIO2->FIOPIN &= ~(0x1FF);

    vTaskDelay(100);
}

void FRITOS::splashscreen(void)
{
    char splash[16][32] =
    {
            {7, 4, 7, 4, 7, 4, 7, 4, 7, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
            {4, 7, 4, 7, 4, 7, 4, 7, 4, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7},
            {7, 4, 7, 4, 7, 4, 7, 4, 7, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
            {4, 7, 4, 7, 4, 7, 4, 7, 4, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7},
            {7, 4, 7, 4, 7, 4, 7, 4, 7, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
            {4, 7, 4, 7, 4, 7, 4, 7, 4, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7},
            {7, 4, 7, 4, 7, 4, 7, 4, 7, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
            {4, 7, 4, 7, 4, 7, 4, 7, 4, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7},
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
            {7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7},
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
            {7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7},
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
            {7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7},
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
            {7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7},


};
    for(uint8_t row = 0; row < 8; ++row)
    {
        disableOE();
        set_color_top(0);
        set_color_bottom(0);
        set_row(row);
        for(uint8_t col = 0; col < 32; ++col)
        {
            if(convert_i)
            {
                set_color_bottom(splash[row+8-convert_i*(2*row+1)][col+convert_j*(31-2*col)]);
                set_color_top(splash[row+convert_i*(15-2*row)][col+convert_j*(31-2*col)]);
            }
            else
            {
                set_color_top(splash[row+8-convert_i*(2*row+1)][col+convert_j*(31-2*col)]);
                set_color_bottom(splash[row+convert_i*(15-2*row)][col+convert_j*(31-2*col)]);
                //set_color_top(1);
                //set_color_bottom(1);
            }
            clockTick();
        }
        latchReset();
        enableOE();
        vTaskDelay(1);
    }
}

void FRITOS::displayObject(arrow &test)
{
    //arrow *object;
    //object = &test;

    /*uint8_t arrow_row = 2;
    uint8_t arrow_length = 4;
    uint8_t arrow_color = 1;
    uint8_t arrow_position = 0;*/

    for(uint8_t row = 0; row < 16; ++row)
    {
        disableOE();
        set_color_top(0);
        set_color_bottom(0);
        set_row(row);
        for(uint8_t col = 0; col < 32; ++col)
        {
            /* Correct way to set
            set_color_top(splash[row+8][col]);
            set_color_bottom(splash[row][col]);
             */
            if(test.getRow() == row)
            {
                if((col >= test.getColumn() && (col < (test.getLength() + test.getColumn()))))
                {
                    if(test.getRow() < 8)
                    {
                        set_color_bottom(test.getColor());
                    }
                    else
                    {
                        set_color_top(test.getColor());
                    }
                }
                else
                {
                    set_color_top(0);
                    set_color_bottom(0);
                }
            }
            clockTick();
        }
        latchReset();
        enableOE();
        vTaskDelay(1);
    }
}

void FRITOS::enableOE(void)
{
    LPC_GPIO0->FIOCLR = (1 << OE);
}

void FRITOS::disableOE(void)
{
    LPC_GPIO0->FIOSET = (1 << OE);
}

void FRITOS::clockTick(void)
{
    LPC_GPIO1->FIOSET = (1 << CLK);
    LPC_GPIO1->FIOCLR = (1 << CLK);
}

void FRITOS::latchReset(void)
{
    LPC_GPIO0->FIOSET = (1 << LAT);
    LPC_GPIO0->FIOCLR = (1 << LAT);
}

void FRITOS::set_row(uint8_t row)
{
    uint8_t a_bit = row & 1;
    uint8_t b_bit = (row >> 1) & 1;
    uint8_t c_bit = (row >> 2) & 1;
    a_bit ? LPC_GPIO2->FIOSET = (1 << A) : LPC_GPIO2->FIOCLR = (1 << A);
    b_bit ? LPC_GPIO2->FIOSET = (1 << B) : LPC_GPIO2->FIOCLR = (1 << B);
    c_bit ? LPC_GPIO2->FIOSET = (1 << C) : LPC_GPIO2->FIOCLR = (1 << C);
}

void FRITOS::set_color_bottom(uint32_t color)
{
    if(convert_i)
    {
        uint8_t r2_bit = color & 1;
        uint8_t g2_bit = (color >> 1) & 1;
        uint8_t b2_bit = (color >> 2) & 1;
        r2_bit ? LPC_GPIO2->FIOSET = (1 << R2) : LPC_GPIO2->FIOCLR = (1 << R2);
        g2_bit ? LPC_GPIO2->FIOSET = (1 << G2) : LPC_GPIO2->FIOCLR = (1 << G2);
        b2_bit ? LPC_GPIO2->FIOSET = (1 << B2) : LPC_GPIO2->FIOCLR = (1 << B2);
    }
    else
    {
        uint8_t r1_bit = color & 1;
        uint8_t g1_bit = (color >> 1) & 1;
        uint8_t b1_bit = (color >> 2) & 1;
        r1_bit ? LPC_GPIO2->FIOSET = (1 << R1) : LPC_GPIO2->FIOCLR = (1 << R1);
        g1_bit ? LPC_GPIO2->FIOSET = (1 << G1) : LPC_GPIO2->FIOCLR = (1 << G1);
        b1_bit ? LPC_GPIO2->FIOSET = (1 << B1) : LPC_GPIO2->FIOCLR = (1 << B1);
    }

}

void FRITOS::set_color_top(uint32_t color)
{
    if(convert_i)
    {
        uint8_t r1_bit = color & 1;
        uint8_t g1_bit = (color >> 1) & 1;
        uint8_t b1_bit = (color >> 2) & 1;
        r1_bit ? LPC_GPIO2->FIOSET = (1 << R1) : LPC_GPIO2->FIOCLR = (1 << R1);
        g1_bit ? LPC_GPIO2->FIOSET = (1 << G1) : LPC_GPIO2->FIOCLR = (1 << G1);
        b1_bit ? LPC_GPIO2->FIOSET = (1 << B1) : LPC_GPIO2->FIOCLR = (1 << B1);
    }
    else
    {
        uint8_t r2_bit = color & 1;
        uint8_t g2_bit = (color >> 1) & 1;
        uint8_t b2_bit = (color >> 2) & 1;
        r2_bit ? LPC_GPIO2->FIOSET = (1 << R2) : LPC_GPIO2->FIOCLR = (1 << R2);
        g2_bit ? LPC_GPIO2->FIOSET = (1 << G2) : LPC_GPIO2->FIOCLR = (1 << G2);
        b2_bit ? LPC_GPIO2->FIOSET = (1 << B2) : LPC_GPIO2->FIOCLR = (1 << B2);
    }

}

