#if 1
#include "FRITOS.hpp"

#include "tasks.hpp"
#include "LPC17xx.h"
#include "FreeRTOS.h"
#include "stdio.h"
#include "uart0_min.h"
#include "storage.hpp"
#include "event_groups.h"
#include <string.h>
#include "arrow.hpp"
#include "balloons.hpp"

#define DEBUG   1
#define DEMO    0
SemaphoreHandle_t xMutex;

#define row               0
#define arrow_length      3
#define arrow_position    0
#define color             7

arrow staticArrow(row, arrow_length, arrow_position, color);
arrow shootArrow(row, 1, (arrow_position+arrow_length-1), color);

void switch_init(void)
{
    //Switch 0 at P1.9
    LPC_PINCON->PINSEL2 &= ~(0x3 << 18);            //Set as GPIO pin
    LPC_GPIO1->FIODIR &= ~(1 << 9);                 //Set switch as input

    //Switch 1 at P1.10
    LPC_PINCON->PINSEL2 &= ~(0x3 << 20);
    LPC_GPIO1->FIODIR &= ~(1 << 10);

    //Switch 2 at P1.14
    LPC_PINCON->PINSEL2 &= ~(0x3 << 28);
    LPC_GPIO1->FIODIR &= ~(1 << 14);

    //Switch 3 at P1.15
    LPC_PINCON->PINSEL2 &= ~(0x3 << 30);
    LPC_GPIO1->FIODIR &= ~(1 << 15);
}

void testRGB(void * params)
{
    FRITOS sjone(DEMO);
    sjone.initRGB();
    delay_ms(1000);
    printf("testRGB");

    while(1)
    {
        sjone.splashscreen();   //display splash screen before pushes any switch
    }
}

void displayArrow(void *params)
{
    FRITOS sjone(DEMO);
    sjone.initRGB();

    delay_ms(100);
    uart0_puts("test\n");

    while(1)
    {
        sjone.displayObject(staticArrow);
    }
}

void displayShootingArrow(void *params)
{
    FRITOS shootingArrow(DEMO);
    shootingArrow.initRGB();

    delay_ms(100);
    while(1)
    {
        shootingArrow.displayObject(shootArrow);
    }
}

void moveArrow(void *pvParameters)
{
    printf("inside interrupt\n");
    while(1)
    {
        if(LPC_GPIO1->FIOPIN & (1 << 9))
        {
            delay_ms(200);
            staticArrow.incrementRow();
            shootArrow.incrementRow();
            printf("Row: %d\n",staticArrow.getRow());
        }

        if(LPC_GPIO1->FIOPIN & (1 << 10))
        {
            delay_ms(200);
            staticArrow.decrementRow();
            shootArrow.decrementRow();
            printf("Row: %d\n",staticArrow.getRow());
        }
        if(LPC_GPIO1->FIOPIN & (1 << 14))
        {
            delay_ms(200);
            printf("Column: %d\n", shootArrow.getColumn());
            shootArrow.shootArrow();
        }
        if(LPC_GPIO1->FIOPIN & (1 << 15))
        {
            delay_ms(200);
            printf("Generate random balloons: ");
            for(int i = 0; i < 15; i++)
            {
                balloons ran;
                printf("%u\n", ran.balloonPosition());
                delay_ms(1000);

            }
        }
    }
}

int main(void)
{
    const uint32_t STACK_SIZE = 1024;

    switch_init();

    //Use as Background color
    //xTaskCreate(testRGB, "testRGB", STACK_SIZE, NULL, PRIORITY_HIGH, NULL);

    xTaskCreate(displayArrow, "Display Arrow", STACK_SIZE, NULL, PRIORITY_HIGH, NULL);
    xTaskCreate(moveArrow, "Move Arrow", STACK_SIZE, NULL, PRIORITY_HIGH, NULL);
    xTaskCreate(displayShootingArrow, "Shoot Arrow", STACK_SIZE, NULL, 2, NULL);

    vTaskStartScheduler();
    return 0;
}
#endif
