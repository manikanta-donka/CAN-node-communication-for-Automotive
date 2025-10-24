/*
 * File:   ecu1_sensor.c
 * Author: sekha
 *
 * Created on 2 September, 2025, 9:00 AM
 */


#include "ecu1_sensor.h"
#include "adc.h"
#include "can.h"
#include "msg_id.h"
//#include "uart.h"
#include "clcd.h"
#include "digital_keypad.h"
//#include "matrix_keypad.h"

#define _XTAL_FREQ 2000000
uint16_t get_speed()
{
    unsigned short speed = 0;
    unsigned short adc_value = read_adc(CHANNEL4);
    
    speed = (int) adc_value / (float) 10.33;
    
    return speed;
}

unsigned char get_gear_pos()
{
    unsigned char gear[9][3] = {"ON", "GN", "G1", "G2", "G3", "G4", "G5", "GR", "C_"};
    unsigned char key = 0;
    unsigned int current_gear = 0, crash = 0;

    
    key = read_switches(STATE_CHANGE);
    
    if (key == SWITCH1) {
        if (crash) {
            crash = 0;      // Clear crash flag
            current_gear = 1; // Reset to first gear
        } else if (current_gear < 7) {
            current_gear++; // Increment gear
        }
    }
    if (key == SWITCH2) {
        if (crash) {
            crash = 0;      // Clear crash flag
            current_gear = 1; // Reset to first gear
        } else if (current_gear > 1) {
            current_gear--; // Decrement gear
        }
    }
    if (key == SWITCH3) {
        crash = 1;         // Set crash flag
        current_gear = 8;  
    }
    
    return gear[current_gear];
}
