
/*
 * Filename: sc_button_type.h
 *
 * Author: Autogenerated by H-DA RTE Generator, (c) Prof. Fromm
 */

#ifndef _H_DEFINE_SC_BUTTON_TYPE
#define _H_DEFINE_SC_BUTTON_TYPE

#include "project.h"
#include "global.h"
#include "rte_types.h"

/* USER CODE START SC_BUTTON_INCLUDES */

/* USER CODE END SC_BUTTON_INCLUDES */



/**********************************************************************
 *       Type Definition for SC_BUTTON signal    
 **********************************************************************/

/* USER CODE START SC_BUTTON_USERDEFINITIONS */

/* USER CODE END SC_BUTTON_USERDEFINITIONS */

typedef 
/* USER CODE START SC_BUTTON_SIGNALDATADEFINITION */
struct
{
    uint8_t index_b4;
    uint8_t index_b3;
    uint8_t index_b2;
    uint8_t index_b1;
    uint16_t timer;
    boolean_t previous_and_current_b4[2];
    boolean_t previous_and_current_b3[2];
	boolean_t previous_and_current_b2[2];
    boolean_t previous_and_current_b1[2];
    boolean_t start_timer_flag;
} 
/* USER CODE END SC_BUTTON_SIGNALDATADEFINITION */
SC_BUTTON_data_t;

/* USER CODE START InitSC_BUTTON */

#define SC_BUTTON_INIT_DATA ((SC_BUTTON_data_t){0,0,0,0,0,{ },{ },{ },{ },0})
/* USER CODE END InitSC_BUTTON */


/**
 * Default IN driver API
 * \param SC_BUTTON_data_t *const data : [OUT] scaled data read from the driver
 * \return RC_SUCCESS is all was ok, error code otherwise
 */
RC_t SC_BUTTON_driverIn(SC_BUTTON_data_t *const data);




/* USER CODE START SC_BUTTON_USERFUNCTIONS */

/* USER CODE END SC_BUTTON_USERFUNCTIONS */


#endif