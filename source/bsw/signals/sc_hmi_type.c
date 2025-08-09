#include "project.h"
#include "global.h"
#include "rte.h"
#include "rte_types.h"
#include "sc_hmi_type.h"



/* USER CODE START SC_HMI_INCLUDE */
#include "tft.h"
#include "debug_rte.h"
#include "stdlib.h"
/* USER CODE END SC_HMI_INCLUDE */


/*
* description: Signalclass
* name: sc_hmi
* shortname: hmi
*/

/* USER CODE START SC_HMI_USERDEFINITIONS */

/* USER CODE END SC_HMI_USERDEFINITIONS */


/*****************************************************************************************
 *************** Port Wrapper Implementation for SC_HMI signal  ****************
 *****************************************************************************************/
 
 
/**
 * Default OUT driver API
 */
inline RC_t SC_HMI_driverOut(const SC_HMI_data_t  *const data)
{
	/* USER CODE START driverOutSC_HMI */
    if(data->clear_screen)
    {
        TFT_clearScreen();
    }
    if(data->update_game)
    {
        //clear old 
        TFT_fillRect(data->pong.bat_1_y_old_position, data->pong.bat_1_x_old_position, WIDTH_RECTANGLE, HIGHT_RECTANGLE, BLACK);
        TFT_fillRect(data->pong.bat_2_y_old_position, data->pong.bat_2_x_old_position, WIDTH_RECTANGLE, HIGHT_RECTANGLE, BLACK);
        //draw new
        TFT_fillRect(data->pong.bat_1_y_position, data->pong.bat_1_x_position, WIDTH_RECTANGLE, HIGHT_RECTANGLE, WHITE);
        TFT_fillRect(data->pong.bat_2_y_position, data->pong.bat_2_x_position, WIDTH_RECTANGLE, HIGHT_RECTANGLE, WHITE);
        //clear old
        //fill new
        TFT_fillCircle(data->pong.ball_y_position, data->pong.ball_x_position, BALL_RADIUS, WHITE);
    }
    else if(data->update_menue)
    {
        TFT_clearScreen();
        TFT_setTextSize(3);
        TFT_setCursor(20,10);
        TFT_println("MENUE");
        TFT_setCursor(20,CURSER_POS_PONG);
        TFT_setTextSize(2);
        TFT_println("PONG");
        TFT_setCursor(20,CURSER_POS_SNAKE);
        TFT_println("SNAKE");
        TFT_setCursor(20,CURSER_POS_SOKKER);
        TFT_println("SOKKER");
        TFT_setCursor(CURSER_POS,data->menue_curser);
        TFT_println("*");
    }
    else if(data->update_pause)
    {
        UART_LOG_PutString("update_pause\r\n");
        TFT_clearScreen();
        TFT_setTextSize(3);
        TFT_setCursor(20,60);
        TFT_println("PAUSE");
    }

	return RC_SUCCESS;
	/* USER CODE END driverOutSC_HMI */
}



