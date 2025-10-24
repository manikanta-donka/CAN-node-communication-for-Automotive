/*
 * File:   ecu1_main.c
 * Author: Manikanta Donka
 * Description: CAN node communication for automation.
 * Created on 2 September, 2025, 8:58 AM
 */


#include "adc.h"
#include "can.h"
#include "ecu1_sensor.h"
#include "msg_id.h"
//#include "uart.h"
#include "matrix_keypad.h"
#include "clcd.h"


void init_config()
{
    init_matrix_keypad();
    init_adc();
    init_can();
//    init_uart();
    
}

int main()
{
    init_config();
    unsigned short speed;
    unsigned char gear;
    while(1)
    {
        speed = get_speed();
        
        gear = get_gear_pos();
        
        can_transmit(SPEED_MSG_ID, &speed, 1);
        __delay_us(1000);
        can_transmit(GEAR_MSG_ID, &gear, 1);
        __delay_us(1000);
    }
   
}
