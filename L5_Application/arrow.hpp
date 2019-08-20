/*
 * arrow.hpp
 *
 *  Created on: Nov 18, 2018
 *      Author: Aaron
 */

#ifndef ARROW_HPP_
#define ARROW_HPP_

#include <stdint.h>
#include "utilities.h"

class arrow
{
public:
    arrow(volatile uint8_t row_num, uint8_t arrow_length, volatile uint8_t col_pos, uint8_t color_typ);
    ~arrow();
    uint8_t getRow(void);
    uint8_t getLength(void);
    uint8_t getColumn(void);
    uint8_t getColor(void);
    void incrementRow(void);
    void decrementRow(void);
    void shootArrow(void);

private:
    uint8_t row;
    uint8_t length;
    uint8_t color;
    uint8_t position;
};

#endif /* ARROW_HPP_ */
