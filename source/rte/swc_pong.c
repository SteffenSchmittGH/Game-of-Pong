

/*
 * Filename: swc_pong.c
 *
 * Author: Autogenerated by H-DA RTE Generator, (c) Prof. Fromm
 */

#include "project.h"
#include "global.h"
#include "rte.h"
#include "rte_types.h"
#include "swc_pong.h"



/* USER CODE START SWC_PONG_INCLUDE */
#include "mailbox.h"
#include "statemachine.h"
#include "debug_rte.h" //DEFINES
#include "stdlib.h"

#include "games.h"
/* USER CODE END SWC_PONG_INCLUDE */


#include "sp_common.h"

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
void PONG_joy_run(RTE_event ev){
	
	/* USER CODE START PONG_joy_run */
    //UART_LOG_PutString("joy!\r\n");
    RTE_SC_JOYSTICK_pullPort(&SO_JOYSTICK_signal);
    SC_JOYSTICK_data_t joystick_datas;
    joystick_datas = RTE_SC_JOYSTICK_get(&SO_JOYSTICK_signal);
    sint16_t formatted_joystick_data;
    formatted_joystick_data = joystick_datas.joystick_vertical - JOYSTICK_VERTICAL_OFFSET;
    SC_EVENT_data_t event_signal;
    event_signal.event_statemachine = EV_SO_JOY_NO;
    SC_EVENT_data_t trigger_statemachine;
    // in order to fire no joysick signal event just once
    static boolean_t nosignal_first = TRUE;
    //can be improved by biased multiplex
    if(formatted_joystick_data > 1800)
    {
        //UART_LOG_PutString("up_highspeed\r\n");
        event_signal.event_statemachine = EV_SO_JOY_UP;
    }
    else if(formatted_joystick_data > 1000)
    {
        //UART_LOG_PutString("up_medspeed\r\n");
        event_signal.event_statemachine = EV_SO_JOY_UP;
    }
    else if(formatted_joystick_data > 200)
    {
        //UART_LOG_PutString("up_lowhspeed\r\n");
        event_signal.event_statemachine = EV_SO_JOY_UP;
    }
    else if(formatted_joystick_data < -1800)
    {
        //UART_LOG_PutString("down_highspeed\r\n");
        event_signal.event_statemachine = EV_SO_JOY_DOWN;
    }
    else if(formatted_joystick_data < -1000)
    {
        //UART_LOG_PutString("down_medspeed\r\n");
        event_signal.event_statemachine = EV_SO_JOY_DOWN;
    }
    else if(formatted_joystick_data < -20)
    {
        //UART_LOG_PutString("down_lowspeed\r\n");
        event_signal.event_statemachine = EV_SO_JOY_DOWN;
    }
    else if(formatted_joystick_data < 200)
    {
        //UART_LOG_PutString("NO MOVE\r\n");
        event_signal.event_statemachine = EV_SO_JOY_NO;
    }
    //If event occoured, write it to message buffer and fire event via onDataUpdate
    if(event_signal.event_statemachine != EV_SO_JOY_NO)
    {
        MESSAGEBOX_PUT(&event_queue, (void*)&event_signal, MB_TYPE_EVENTSIGNAL ,sizeof(event_signal) + 1);
        RTE_SC_EVENT_set(&SO_EVENT_signal, trigger_statemachine);
        nosignal_first = (!nosignal_first) ? TRUE : FALSE;
        //UART_LOG_PutString("SEND\r\n");
    }
    if(nosignal_first && event_signal.event_statemachine == EV_SO_JOY_NO)
    {
        MESSAGEBOX_PUT(&event_queue, (void*)&event_signal, MB_TYPE_EVENTSIGNAL ,sizeof(event_signal) + 1);
        RTE_SC_EVENT_set(&SO_EVENT_signal, trigger_statemachine);
        nosignal_first = FALSE;
        //UART_LOG_PutString("EV_JOY_NONE\r\n");
    }
    //UART_LOG_PutString("joystick runnable\r\n");
    #if DEBUG_JOYSTICK_RUNNABLE
        char buf[10];
        itoa(formatted_joystick_data,buf,10);
        UART_LOG_PutString("joy vertical: ");
        UART_LOG_PutString(buf);
        UART_LOG_PutString("\r\n");
    #endif
    /* USER CODE END PONG_joy_run */
}

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
void PONG_button_run(RTE_event ev){
	
	/* USER CODE START PONG_button_run */
    RTE_SC_BUTTON_pullPort(&SO_BUTTONS_signal);
    SC_BUTTON_data_t button_datas;
    button_datas = RTE_SC_BUTTON_get(&SO_BUTTONS_signal);
    SC_EVENT_data_t event_datas;
    event_datas.event_statemachine = EV_STATE_NONE;
    SC_EVENT_data_t update_trigger;
    //UART_LOG_PutString("button!\r\n");
    if(button_datas.previous_and_current_b1[button_datas.index_b2] == 1 && button_datas.previous_and_current_b1[!button_datas.index_b2] == 0)//falling edge
    {
        #if ENABLE_LONG_PRESS_DETECTION
        if(button_datas.timer > 40)
        {
            event_datas.event_statemachine = EV_SO_B1;
            UART_LOG_PutString("EV_KRLP\r\n"); 
        }
        if(button_datas.timer <= 20)
        {
            event_datas.event_statemachine = EV_SO_B1LP;
            UART_LOG_PutString("EV_KR\r\n");
        }
        #else  
           //UART_LOG_PutString("B1\r\n"); 
           event_datas.event_statemachine = EV_SO_B1;    
        #endif
    }
    if(button_datas.previous_and_current_b2[button_datas.index_b2] == 1 && button_datas.previous_and_current_b2[!button_datas.index_b2] == 0)//falling edge
    {
        #if ENABLE_LONG_PRESS_DETECTION
        if(button_datas.timer > 40)
        {
            event_datas.event_statemachine = EV_SO_B2;
            UART_LOG_PutString("EV_KRLP\r\n"); 
        }
        if(button_datas.timer <= 20)
        {
            event_datas.event_statemachine = EV_SO_B2LP;
            UART_LOG_PutString("EV_KR\r\n");
        }
        #else
            //UART_LOG_PutString("B2\r\n"); 
            event_datas.event_statemachine = EV_SO_B2;
        #endif
    }
    if(button_datas.previous_and_current_b3[button_datas.index_b3] == 1 && button_datas.previous_and_current_b3[!button_datas.index_b3] == 0)//falling edge
    {
        #if ENABLE_LONG_PRESS_DETECTION
        if(button_datas.timer > 40)
        {
            event_datas.event_statemachine = EV_SO_B3;
            UART_LOG_PutString("EV_KRLP\r\n"); 
        }
        if(button_datas.timer <= 20)
        {
            event_datas.event_statemachine = EV_SO_B3LP;
            UART_LOG_PutString("EV_KR\r\n");
        }
        #else   
            //UART_LOG_PutString("B3\r\n"); 
            event_datas.event_statemachine = EV_SO_B3;
        #endif
    }
    if(button_datas.previous_and_current_b4[button_datas.index_b4] == 1 && button_datas.previous_and_current_b4[!button_datas.index_b4] == 0)//falling edge
    {
        #if ENABLE_LONG_PRESS_DETECTION
        if(button_datas.timer > 40)
        {
            event_datas.event_statemachine = EV_SO_B4;
            UART_LOG_PutString("EV_KRLP\r\n"); 
        }
        if(button_datas.timer <= 20)
        {
            event_datas.event_statemachine = EV_SO_B4LP;
            UART_LOG_PutString("EV_KR\r\n");
        }
        #else
            //UART_LOG_PutString("B4\r\n"); 
            event_datas.event_statemachine = EV_SO_B4;
        #endif
    }
    if(event_datas.event_statemachine != EV_STATE_NONE)
    {
        MESSAGEBOX_PUT(&event_queue, (void*)&event_datas,MB_TYPE_EVENTSIGNAL, sizeof(event_datas) + 1);
        RTE_SC_EVENT_set(&SO_EVENT_signal, update_trigger);
    }
    /* USER CODE END PONG_button_run */
}

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
void PONG_control_run(RTE_event ev){
	
	/* USER CODE START PONG_control_run */
    //UART_LOG_PutString("control\r\n");
    SC_EVENT_data_t local_event_data;
    MESSAGEBOX_GET(&event_queue, &local_event_data, event_queue.messagebox_buffer->buffer_size);
    if(local_event_data.event_statemachine == EV_SO_B1)
    {
        processEvent_Container(&sm_container_active,EV_B1);
        //UART_LOG_PutString("MESSAGEBOX_WORKS_B1\r\n");
    }
    else if(local_event_data.event_statemachine == EV_SO_B2)
    {
        processEvent_Container(&sm_container_active,EV_B2);
        //UART_LOG_PutString("MESSAGEBOX_WORKS_B2\r\n");
    }
    else if(local_event_data.event_statemachine == EV_SO_B3)
    {
        processEvent_Container(&sm_container_active,EV_B3);
        //UART_LOG_PutString("MESSAGEBOX_WORKS_B3\r\n");
    }
    else if(local_event_data.event_statemachine == EV_SO_B4)
    {
        processEvent_Container(&sm_container_active,EV_B4);
        //UART_LOG_PutString("MESSAGEBOX_WORKS_B4\r\n");
    }
    else if(local_event_data.event_statemachine == EV_SO_JOY_DOWN)
    {
        processEvent_Container(&sm_container_active,EV_JOY_DOWN);
        //UART_LOG_PutString("MESSAGEBOX_WORKS_DOWN\r\n");
    }
    else if(local_event_data.event_statemachine == EV_SO_JOY_UP)
    {
        processEvent_Container(&sm_container_active,EV_JOY_UP);
        //UART_LOG_PutString("MESSAGEBOX_WORKS_JOYUP\r\n");
    }else if(local_event_data.event_statemachine == EV_SO_JOY_NO)
    {
        processEvent_Container(&sm_container_active,EV_JOY_NONE);
        //UART_LOG_PutString("MESSAGEBOX_WORKS_JOYUP\r\n");
    }
    else
    {
        UART_LOG_PutString("else control\r\n");
    }
    
    /* USER CODE END PONG_control_run */
}

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
void PONG_hmi_run(RTE_event ev){
	
	/* USER CODE START PONG_hmi_run */
    //UART_LOG_PutString("hmi runnable\r\n");
    GAMES_SCREEN_TYPES_t  type;
    SC_PONG_data_t game_data = RTE_SC_PONG_get(&SO_GAME_signal);
    SC_MENUE_data_t menue_data = RTE_SC_MENUE_get(&SO_MENUE_signal);
    type = menue_data.games_current;
    SC_HMI_data_t hmi_data;
    switch (type) {
        case GAMES_SCREEN_PONG: {
            
            hmi_data.update_game = TRUE;
            //ball
            hmi_data.pong.ball_x_position = game_data.game.ball.x_position;
            hmi_data.pong.ball_y_position = game_data.game.ball.y_position;
            //bats xpos
            hmi_data.pong.bat_1_x_old_position = hmi_data.pong.bat_1_x_position;
            hmi_data.pong.bat_1_x_position = game_data.game.bat_1.x_position;
            hmi_data.pong.bat_2_x_old_position = hmi_data.pong.bat_2_x_position;
            hmi_data.pong.bat_2_x_position = game_data.game.bat_2.x_position;
            //bats ypos
            hmi_data.pong.bat_1_y_old_position = hmi_data.pong.bat_1_y_position;
            hmi_data.pong.bat_1_y_position = game_data.game.bat_1.y_position;
            hmi_data.pong.bat_2_y_old_position = hmi_data.pong.bat_2_y_position;
            hmi_data.pong.bat_2_y_position = game_data.game.bat_2.y_position;
    
            hmi_data.clear_screen = game_data.clear_screen;
            
            RTE_SC_HMI_set(&SO_TFT_signal, hmi_data);
            RTE_SC_HMI_pushPort(&SO_TFT_signal);
            menue_data.games_current = GAMES_SCREEN_NONE;
            break;
        }
        case GAMES_SCREEN_PAUSE: {
            hmi_data.update_pause = TRUE;
            RTE_SC_HMI_set(&SO_TFT_signal, hmi_data);
            RTE_SC_HMI_pushPort(&SO_TFT_signal);
            menue_data.games_current = GAMES_SCREEN_NONE;
            break;
        }
        case GAMES_SCREEN_MENUE: {
            hmi_data.menue_curser = game_data.menue_curser_pos;
            hmi_data.update_menue = TRUE;
            RTE_SC_HMI_set(&SO_TFT_signal, hmi_data);
            RTE_SC_HMI_pushPort(&SO_TFT_signal);
            menue_data.games_current = GAMES_SCREEN_NONE;
            break;
        }
        default:
           // UART_LOG_PutString("update tft else\r\n");
            break;
    }
    RTE_SC_MENUE_set(&SO_MENUE_signal, menue_data);
    hmi_data.update_game = FALSE;
    hmi_data.update_menue = FALSE;
    hmi_data.update_pause = FALSE;
    hmi_data.clear_screen = FALSE;
    RTE_SC_HMI_set(&SO_TFT_signal, hmi_data);
    game_data.clear_screen = FALSE;
    RTE_SC_PONG_set(&SO_GAME_signal, game_data);
    /* USER CODE END PONG_hmi_run */
}

/* USER CODE START SWC_PONG_FUNCTIONS */

/* USER CODE END SWC_PONG_FUNCTIONS */

