

#ifndef _H_DEFINE_SC_EVENT_TYPE
#define _H_DEFINE_SC_EVENT_TYPE

#include "project.h"
#include "global.h"
#include "rte_types.h"

/* USER CODE START SC_EVENT_INCLUDES */

/* USER CODE END SC_EVENT_INCLUDES */



/**********************************************************************
 *       Type Definition for SC_EVENT signal    
 **********************************************************************/

/* USER CODE START SC_EVENT_USERDEFINITIONS */
typedef enum {
    EV_SO_B1,
    EV_SO_B2,
    EV_SO_B3,
    EV_SO_B4,
    EV_SO_JOY_UP,
    EV_SO_JOY_DOWN,
    EV_SO_JOY_NO,
    #if ENABLE_LONG_PRESS_DETECTION
    EV_SO_B1LP,
    EV_SO_B2LP,
    EV_SO_B3LP,
    EV_SO_B4LP,
    #endif
    EV_STATE_NONE,
}STATE_EVENT_t;
/* USER CODE END SC_EVENT_USERDEFINITIONS */

typedef 
/* USER CODE START SC_EVENT_SIGNALDATADEFINITION */
struct
{
	STATE_EVENT_t event_statemachine;
} 
/* USER CODE END SC_EVENT_SIGNALDATADEFINITION */
SC_EVENT_data_t;

/* USER CODE START InitSC_EVENT */

#define SC_EVENT_INIT_DATA ((SC_EVENT_data_t){EV_STATE_NONE})
/* USER CODE END InitSC_EVENT */





/* USER CODE START SC_EVENT_USERFUNCTIONS */

/* USER CODE END SC_EVENT_USERFUNCTIONS */


#endif
