/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/

/* [] END OF FILE */

#include "sevenSegDriver.h"
#include "SEVEN_CONTROL.h"
#include "SEVEN_SELECT.h"

void init_sev( segment_t seg){
    if(seg == SEG1){
        SEVEN_SELECT_Write(1);
    }else{
        SEVEN_SELECT_Write(0);   
    }
    return;   
}

sign_t getSegSign(){
    return  SEVEN_CONTROL_Read();
}

void setSegSign(sign_t sign){
switch(sign){
    case A: SEVEN_CONTROL_Write(238); break;
    case B: SEVEN_CONTROL_Write(0b11111110); break;
    case C: SEVEN_CONTROL_Write(156); break;
    case D: SEVEN_CONTROL_Write(252); break;
    case E: SEVEN_CONTROL_Write(158); break;
    case F: SEVEN_CONTROL_Write(142); break;
    case ZERO: SEVEN_CONTROL_Write(252); break;
    case EINS: SEVEN_CONTROL_Write(96); break;
    case ZWEI: SEVEN_CONTROL_Write(218); break;
    case DREI: SEVEN_CONTROL_Write(242); break;
    case VIER: SEVEN_CONTROL_Write(102); break;
    case FUENF: SEVEN_CONTROL_Write(182); break;
    case SECHS: SEVEN_CONTROL_Write(188); break;
    case SIEBEN: SEVEN_CONTROL_Write(224); break;
    case ACHT: SEVEN_CONTROL_Write(254); break;
    case NEUN: SEVEN_CONTROL_Write(236); break;
};
    return;   
}