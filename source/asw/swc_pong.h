#ifndef _H_DEFINE_SWC_PONG
#define _H_DEFINE_SWC_PONG

#include "project.h"
#include "global.h"
#include "rte_types.h"

/* USER CODE START SWC_PONG_INCLUDES */

/* USER CODE END SWC_PONG_INCLUDES */



/* USER CODE START SWC_PONG_USERDEFINITIONS */

/* USER CODE END SWC_PONG_USERDEFINITIONS */


/*
* component: swc_pong
* cycletime: 10
* description: Runnable
* events: ev_input_10ms
* name: PONG_joy_run
* shortname: joy
* signalIN: so_joystick
* signalOUT: so_event
* task: tsk_input
*/
void PONG_joy_run(RTE_event ev);

/*
* component: swc_pong
* cycletime: 10
* description: Runnable
* events: ev_input_10ms
* name: PONG_button_run
* shortname: button
* signalIN: so_buttons
* signalOUT: so_event
* task: tsk_input
*/
void PONG_button_run(RTE_event ev);

/*
* component: swc_pong
* cycletime: 100
* description: Runnable
* events: ev_event_onData
* name: PONG_control_run
* shortname: control
* signalIN: so_event
* signalOUT: so_menue|so_game|so_pause
* task: tsk_control
*/
void PONG_control_run(RTE_event ev);

/*
* component: swc_pong
* cycletime: 250
* description: Runnable
* events: ev_hmi_250ms
* name: PONG_hmi_run
* shortname: hmi
* signalIN: so_menue|so_game|so_pause
* signalOUT: so_tft
* task: tsk_hmi
*/
void PONG_hmi_run(RTE_event ev);


#endif
