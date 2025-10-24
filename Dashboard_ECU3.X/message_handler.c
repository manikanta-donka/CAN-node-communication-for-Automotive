/*
 * File:   message_handler.c
 * Author: sekha
 *
 * Created on 9 September, 2025, 6:27 PM
 */


#include <xc.h>
#include <string.h>
#include "message_handler.h"
#include "msg_id.h"
#include "can.h"
#include "clcd.h"


static unsigned int delay = 0;

void handle_speed_data(uint8_t *data, uint8_t len)
{
    //Implement the speed function
    unsigned char sp = (data[0]/10) + 48;
    unsigned char sp1 = (data[0]%10) + 48;
    clcd_putch(sp,LINE2(0));
    clcd_putch(sp1,LINE2(1));
}

void handle_gear_data(uint8_t *data, uint8_t len) 
{
    //Implement the gear function
    clcd_putch(data[0], LINE2(4));
    clcd_putch(data[1], LINE2(5));
}

void handle_rpm_data(uint8_t *data, uint8_t len) 
{
    //Implement the rpm function
    int line = 8;
    for(int i=0;i<len;i++)
    {
        clcd_putch(data[i],LINE2(line));
        line++;
    }
}

//void handle_engine_temp_data(uint8_t *data, uint8_t len) 
//{
//    //Implement the temperature function
//}

void handle_indicator_data(uint8_t *data, uint8_t len) 
{
    //Implement the indicator function
    IndicatorStatus cur_ind_status = (IndicatorStatus)data[0];
    switch (cur_ind_status)
    {
        case e_ind_left:
            RIGHT_IND_OFF();
            if(delay++ < 50)
                LEFT_IND_ON();
            else if(delay < 100)
                LEFT_IND_OFF();
            else
                delay = 0;
            break;
        case e_ind_right:
            LEFT_IND_OFF();
            if(delay++ < 50)
                RIGHT_IND_ON();
            else if(delay < 100)
                RIGHT_IND_OFF();
            else
                delay = 0;
            break;
        case e_ind_hazard:
            if(delay++ < 50)
            {
                LEFT_IND_ON();
                RIGHT_IND_ON();
            }
            else if(delay < 100)
            {
                LEFT_IND_OFF();
                RIGHT_IND_OFF();
            }
            else
                delay = 0;
            break;
        case e_ind_off:
            PORTB = 0x00;
            delay = 0;
            break;
    }
}

void process_canbus_data() 
{   
    //process the CAN bus data
    unsigned char data[8];
    uint16_t msg_id;
    unsigned char len;
    
    can_receive(&msg_id,data,&len);
    
    if(msg_id == SPEED_MSG_ID)
    {
        handle_speed_data(data,len);
    }
    else if(msg_id == GEAR_MSG_ID)
    {
        handle_gear_data(data,len);
    }
    else if(msg_id == RPM_MSG_ID)
    {
        handle_rpm_data(data,len);
    }
    else if(msg_id == INDICATOR_MSG_ID)
    {
        handle_indicator_data(data,len);
    }
}