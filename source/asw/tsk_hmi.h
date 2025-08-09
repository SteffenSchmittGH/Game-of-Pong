#ifndef _H_DEFINE_TSK_HMI
#define _H_DEFINE_TSK_HMI

#include "project.h"
#include "global.h"
#include "rte_types.h"

/* USER CODE START TSK_HMI_INCLUDES */

/* USER CODE END TSK_HMI_INCLUDES */



/*
* description: Task doing work. Updates HMI Display.
* events: ev_hmi_250ms
* mode: Event
* name: tsk_hmi
* shortname: hmi
* signalpoolsRO: sp_common
* signalpoolsRW: sp_common
* tickEvent: ev_hmi_250ms
* timertickperiod: 1
*/
DeclareTask(tsk_hmi);


#endif
