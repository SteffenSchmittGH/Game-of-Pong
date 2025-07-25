

/*
 * Filename: sc_button_type.c
 *
 * Author: Autogenerated by H-DA RTE Generator, (c) Prof. Fromm
 */

#include "project.h"
#include "global.h"
#include "rte.h"
#include "rte_types.h"
#include "sc_button_type.h"



/* USER CODE START SC_BUTTON_INCLUDE */
#include "debug_rte.h"
/* USER CODE END SC_BUTTON_INCLUDE */


/*
* description: Signalclass
* name: sc_button
* shortname: button
*/

/* USER CODE START SC_BUTTON_USERDEFINITIONS */

/* USER CODE END SC_BUTTON_USERDEFINITIONS */


/*****************************************************************************************
 *************** Port Wrapper Implementation for SC_BUTTON signal  ****************
 *****************************************************************************************/
 
 

/**
 * Default IN driver API
 */
inline RC_t SC_BUTTON_driverIn(SC_BUTTON_data_t *const data)
{
	/* USER CODE START driverInSC_BUTTON */
    //UART_LOG_PutString("HALLO DRIVER\r\n");
    //read time buttons are pressed
    #if ENABLE_LONG_PRESS_DETECTION
    if(data->start_timer_flag)
    {
        data->timer++;
    }
    else
    {
        data->timer = 0;   
    }
    #endif
    
    if(Button_1_Read())
    {
        #if ENABLE_LONG_PRESS_DETECTION
        data->start_timer_flag = 1;
        #endif
        data->previous_and_current_b1[data->index_b1++] = 1;
        data->index_b1 %=2;
    }
    else
    {
        #if ENABLE_LONG_PRESS_DETECTION
        data->start_timer_flag = 0;
        #endif
        data->previous_and_current_b1[data->index_b1++] = 0;
        data->index_b1 %= 2;
    }
    
    if(Button_2_Read())
    {
        #if ENABLE_LONG_PRESS_DETECTION
        data->start_timer_flag = 1;
        #endif
        data->previous_and_current_b2[data->index_b2++] = 1;
        data->index_b2 %=2;
    }
    else
    {
        #if ENABLE_LONG_PRESS_DETECTION
        data->start_timer_flag = 0;
        #endif
        data->previous_and_current_b2[data->index_b2++] = 0;
        data->index_b2 %= 2;
    }
    
    if(Button_3_Read())
    {
        #if ENABLE_LONG_PRESS_DETECTION
        data->start_timer_flag = 1;
        #endif
        data->previous_and_current_b3[data->index_b3++] = 1;
        data->index_b3 %=2;
    }
    else
    {
        #if ENABLE_LONG_PRESS_DETECTION
        data->start_timer_flag = 0;
        #endif
        data->previous_and_current_b3[data->index_b3++] = 0;
        data->index_b3 %= 2;
    }
    
    if(Button_4_Read())
    {
        #if ENABLE_LONG_PRESS_DETECTION
        data->start_timer_flag = 1;
        #endif
        data->previous_and_current_b4[data->index_b4++] = 1;
        data->index_b4 %=2;
    }
    else
    {
        #if ENABLE_LONG_PRESS_DETECTION
        data->start_timer_flag = 0;
        #endif
        data->previous_and_current_b4[data->index_b4++] = 0;
        data->index_b4 %= 2;
    }
    //Debuggin Purpose
    #if DEBUG_BUTTON_DRIVER
    char buf[10];
    itoa(data->previous_and_current[(data->index)],buf,10);
    UART_LOG_PutString("Previous: ");
    UART_LOG_PutString(buf);
    UART_LOG_PutString(" ");
    itoa(data->previous_and_current[!data->index],buf,10);
    UART_LOG_PutString("Current: ");
    UART_LOG_PutString(buf);
    UART_LOG_PutString("\r\n");
    #endif

	//Read data from the MCAL driver

	//Scale it to the application type

	return RC_SUCCESS;
	/* USER CODE END driverInSC_BUTTON */
}



