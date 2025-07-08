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
#include "global.h"

typedef enum {
    LED_ON,
    LED_OFF,
}LED_ONOF_t;

typedef enum {
    LED_RED,
    LED_GREEN,
    LED_YELLOW,
    LED_ALL,
}LED_id_t;

RC_t my_LED_init();
RC_t my_LED_Set(LED_id_t ledid, LED_ONOF_t led_onof);
RC_t my_LED_Toggle(LED_id_t ledid);
RC_t my_LED_RGB_Set(uint8_t red, uint8_t green, uint8_t blue);
