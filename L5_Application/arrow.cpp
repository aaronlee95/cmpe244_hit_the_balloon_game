#include "arrow.hpp"

arrow::arrow(volatile uint8_t row_num, uint8_t arrow_length, volatile uint8_t col_pos, uint8_t color_typ)
{
    row = row_num;
    length = arrow_length;
    position = col_pos;
    color = color_typ;
}

arrow::~arrow()
{
}

uint8_t arrow::getRow(void)
{
    return row;
}

uint8_t arrow::getLength(void)
{
    return length;
}

uint8_t arrow::getColumn(void)
{
    return position;
}

uint8_t arrow::getColor(void)
{
    return color;
}

void arrow::incrementRow(void)
{
    if(row < 15)
    {
        row++;
    }
    else
    {
        row = 0;
    }
}

void arrow::decrementRow(void)
{
    if(0 == row)
    {
        row = 15;
    }
    else
    {
        row--;
    }
}

void arrow::shootArrow(void)
{
    for(uint8_t i = 0; i < 32; i++)
    {
        if(31 == position)
        {
            position = 0;
        }
        else
        {
            position++;
            delay_ms(200);
        }
    }


}
