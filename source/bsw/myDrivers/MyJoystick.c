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

#include "MyJoystick.h"
#include "ADC_Joy.h"

RC_t joystick_init(){
    ADC_Joy_Start();
}

joystick_t joystick_get_horizontal(){
    int16_t result;
    // result = ADC_Joy_GetResult16(0);
    ADC_Joy_StartConvert();
    while(ADC_Joy_IsEndConversion(ADC_Joy_RETURN_STATUS) == 0);
    result = ADC_Joy_GetResult16(0);
    //ADC_Joy_Stop();
    if(result > 140){
        return right; 
    }else if (result < 120){
        return left;
    }else{
        return initial;
    }
}

joystick_t joystick_get_vertical(){
    int16_t result;
    //ADC_Joy_Start();
    result = ADC_Joy_GetResult16(1);
    //ADC_Joy_Stop();
    if(result > 140){
        return up; 
    }else if (result < 120){
        return down;
    }else{
        return initial;
    }
}