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
#include <global.h>

typedef enum {
    up,
    down,
    left,
    right,
    initial,
}joystick_t;

RC_t joystick_init();
joystick_t joystick_get_horizontal();
joystick_t joystick_get_vertical();
/* [] END OF FILE */
