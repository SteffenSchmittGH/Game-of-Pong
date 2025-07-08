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
#include "myLED.h"
#include "led_G.h"
#include "led_R.h"
#include "led_Y.h"
#include "led_green_rgb.h"
#include "led_red_rgb.h"
#include "led_blue_rgb.h"
#include "PWM_1.h"
#include "PWM_2.h"
#include "PWM_3.h"

const static uint16 LED__Pulse_Width[256] = {
0, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3,
3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 5, 5, 5, 5, 5, 6, 6, 6, 6, 7,
7, 7, 8, 8, 8, 9, 9, 10, 10, 10, 11, 11, 12, 12, 13, 13, 14, 15,
15, 16, 17, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29,
31, 32, 33, 35, 36, 38, 40, 41, 43, 45, 47, 49, 52, 54, 56, 59,
61, 64, 67, 70, 73, 76, 79, 83, 87, 91, 95, 99, 103, 108, 112,
117, 123, 128, 134, 140, 146, 152, 159, 166, 173, 181, 189, 197,
206, 215, 225, 235, 245, 256, 267, 279, 292, 304, 318, 332, 347,
362, 378, 395, 412, 431, 450, 470, 490, 512, 535, 558, 583, 609,
636, 664, 693, 724, 756, 790, 825, 861, 899, 939, 981, 1024, 1069,
1117, 1166, 1218, 1272, 1328, 1387, 1448, 1512, 1579, 1649, 1722,
1798, 1878, 1961, 2048, 2139, 2233, 2332, 2435, 2543, 2656, 2773,
2896, 3025, 3158, 3298, 3444, 3597, 3756, 3922, 4096, 4277, 4467,
4664, 4871, 5087, 5312, 5547, 5793, 6049, 6317, 6596, 6889, 7194,
7512, 7845, 8192, 8555, 8933, 9329, 9742, 10173, 10624, 11094,
11585, 12098, 12634, 13193, 13777, 14387, 15024, 15689, 16384,
17109, 17867, 18658, 19484, 20346, 21247, 22188, 23170, 24196,
25267, 26386, 27554, 28774, 30048, 31378, 32768, 34218, 35733,
37315, 38967, 40693, 42494, 44376, 46340, 48392, 50534, 52772,
55108, 57548, 60096, 62757, 65535
};

static LED_ONOF_t sLED[LED_ALL] = { LED_OFF, LED_OFF, LED_OFF };

RC_t my_LED_init(){
    led_R_Write(0);
    led_G_Write(0);
    led_Y_Write(0);
    led_red_rgb_Write(0);
    led_green_rgb_Write(0);
    led_blue_rgb_Write(0);
    //PWM_1_Init(); 
    //PWM_2_Init(); 
    //PWM_3_Init();
    for(int i = 0; i < LED_ALL; i++){
        sLED[i] = LED_OFF;   
    }
    return RC_SUCCESS;
}
RC_t my_LED_Set(LED_id_t ledid, LED_ONOF_t led_onof){
    if(ledid == LED_RED){
        switch(led_onof){
            case LED_OFF: led_R_Write(0); sLED[ledid] = LED_OFF; break;
            case LED_ON: led_R_Write(1); sLED[ledid] = LED_ON; break;
        }
    }else if(ledid == LED_GREEN){
        switch(led_onof){
            case LED_OFF: led_G_Write(0); sLED[ledid] = LED_OFF; break;
            case LED_ON: led_G_Write(1); sLED[ledid] = LED_ON; break;
        }
    }else if (ledid == LED_YELLOW){
        switch(led_onof){
            case LED_OFF: led_Y_Write(0); sLED[ledid] = LED_OFF; break;
            case LED_ON: led_Y_Write(1); sLED[ledid] = LED_ON; break;
        }
    }else if(ledid == LED_ALL){
        switch(led_onof){
            case LED_OFF: led_R_Write(0); 
                          led_G_Write(0);
                          led_Y_Write(0);
                          for(int i = 0; i < LED_ALL; i++){
                            sLED[i] = LED_OFF;
                          }
                          break;
            case LED_ON: led_R_Write(1); 
                          led_G_Write(1);
                          led_Y_Write(1);
                          sLED[0] = LED_ON;
                          sLED[1] = LED_ON;
                          sLED[2] = LED_ON;
                          for(int i = 0; i < LED_ALL; i++){
                            sLED[i] = LED_ON;
                          }
                          break;
        }
    }else{
        return RC_ERROR; 
    }
    return RC_SUCCESS;
}
RC_t my_LED_Toggle(LED_id_t ledid){
    switch(ledid){
        case LED_RED: ( sLED[LED_RED] == LED_OFF) ? led_R_Write(1) : led_R_Write(0); break;
        case LED_GREEN: (sLED[LED_GREEN] == LED_OFF) ? led_G_Write(1) : led_G_Write(0); break;
        case LED_YELLOW: (sLED[LED_YELLOW] == LED_OFF) ? led_Y_Write(1) : led_Y_Write(0); break;
        case LED_ALL: 
            (sLED[LED_RED] == LED_OFF) ? led_R_Write(1) : led_R_Write(0);
            (sLED[LED_GREEN] == LED_OFF) ? led_G_Write(1) : led_G_Write(0);
            (sLED[LED_YELLOW] == LED_OFF) ? led_Y_Write(1) : led_Y_Write(0);
            break;
    }
    return RC_SUCCESS;
}
RC_t my_LED_RGB_Set(uint8_t red, uint8_t green, uint8_t blue){
    PWM_1_WritePeriod(LED__Pulse_Width[red]);
    PWM_2_WritePeriod(LED__Pulse_Width[green]);
    PWM_3_WritePeriod(LED__Pulse_Width[blue]);
    return RC_SUCCESS;
}