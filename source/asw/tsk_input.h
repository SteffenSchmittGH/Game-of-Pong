#ifndef _H_DEFINE_TSK_INPUT
#define _H_DEFINE_TSK_INPUT

#include "project.h"
#include "global.h"
#include "rte_types.h"

/* USER CODE START TSK_INPUT_INCLUDES */

/* USER CODE END TSK_INPUT_INCLUDES */



/*
* description: Task doing work. Handles input Data. From Joystick, Buttons and whatever should be added in future. Maybe UART.
* events: ev_input_10ms
* mode: Event
* name: tsk_input
* shortname: input
* signalpoolsRO: sp_common
* signalpoolsRW: sp_common
* tickEvent: ev_input_10ms
* timertickperiod: 1
*/
DeclareTask(tsk_input);


#endif
