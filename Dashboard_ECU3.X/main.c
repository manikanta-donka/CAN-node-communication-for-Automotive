/*
 * File:   main.c
 * Author: Manikanta Donka
 * Description: CAN node communication for automation
 * Created on 9 September, 2025, 6:27 PM
 */


#include <xc.h>
#include <stdint.h>
#include "can.h"
#include "clcd.h"
#include "msg_id.h"
#include "message_handler.h"
//#include "isr.h"
#include "timer0.h"

static void init_leds() {
    TRISB = 0x08; // Set RB2 as output, RB3 as input, remaining as output
    PORTB = 0x00;
}

static void init_config(void) {
    // Initialize CLCD and CANBUS
    init_clcd();
    init_can();
    init_leds();

    // Enable Interrupts
    PEIE = 1;
    GIE = 1;
    init_timer0();
}

void main(void) {
    // Initialize peripherals
    init_config();
    TRISB = TRISB & 0x3c;

    /* ECU1 main loop */
    clcd_print("                ",LINE2(0));
    while (1) {
        // Read CAN Bus data and handle it
        clcd_print("SP",LINE1(0));
        clcd_print("GEAR",LINE1(3));
        clcd_print("RPM",LINE1(8));
        clcd_print("IND",LINE1(13));
        process_canbus_data();
    }

    return;
}

