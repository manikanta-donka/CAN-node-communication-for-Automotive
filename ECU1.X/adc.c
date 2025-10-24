/*
 * File:   adc.c
 * Author: sekha
 *
 * Created on 2 September, 2025, 9:01 AM
 */


#include <xc.h>
#include "adc.h"

void init_adc_config()
{
    init_adc();
}
    
void init_adc()
{
    // Channel 4
    CHS3 = 0;
    CHS2 = 1;
    CHS1 = 0;
    CHS0 = 0;
    
    // No Conversion
    GO = 0;
    
    // ADC Enable
    ADON = 1;
    
    //No Referance voltage
    VCFG1 = 0;
    VCFG0 = 0;
    
    //Make AN4 as analog
    PCFG3 = 1;
    PCFG2 = 0;
    PCFG1 = 1;
    PCFG0 = 0;
    
    //0.0625 MHz of clock
    ADCS2 = 0;
    ADCS1 = 1;
    ADCS0 = 0;
    
    // Acquisition time 8TAD
    ACQT2 = 1;
    ACQT1 = 0;
    ACQT0 = 0;
    
    ADFM = 1;   // Right justified
    ADRESH = ADRESL = 0x00;
}

unsigned short read_adc(unsigned char channel)
{
	unsigned short reg_val;

	/*select the channel*/
	ADCON0 = (ADCON0 & 0xC3) | (channel << 2);

	/* Start the conversion */
	GO = 1;
	while (GO);
	reg_val = (ADRESH << 8) | ADRESL; 

	return reg_val;
}
    
