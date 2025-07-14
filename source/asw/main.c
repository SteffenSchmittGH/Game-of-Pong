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
#include "project.h"

#include "statemachine.h"
#include "mailbox.h"
#include "tft.h"


/*
Regarding ErrorHandling: 
    First Step should be Return Codes.
    Second Step could be AGE.
    What about Central Error Handler.
*/
//ISR which will increment the systick counter every ms
ISR(systick_handler)
{
    CounterTick(cnt_systick);
}

int main()
{
    CyGlobalIntEnable; /* Enable global interrupts. */
   
    //Set systick period to 1 ms. Enable the INT and start it.
	EE_systick_set_period(MILLISECONDS_TO_TICKS(1, BCLK__BUS_CLK__HZ));
	EE_systick_enable_int();
   
    // Start Operating System
    for(;;)	    
    	StartOS(OSDEFAULTAPPMODE);
}

void unhandledException()
{
    //Ooops, something terrible happened....check the call stack to see how we got here...
    __asm("bkpt");
}

ALARMCALLBACK(task_activation)
{
    static uint16_t callback_counter = 0;
    callback_counter = ( callback_counter + 1 ) % 2001;
    if(callback_counter % 11 == 0){
        SetEvent(tsk_input, ev_input_10ms);
    }
    if(callback_counter % 251 == 0){
        //UART_LOG_PutString("hmi callback\r\n");
        SetEvent(tsk_hmi, ev_hmi_250ms);
    }
    //UART_LOG_PutString("CALLBACK\r\n");
}

/********************************************************************************
 * Task Definitions
 ********************************************************************************/

TASK(tsk_init)
{
    
    //Init MCAL Drivers
    ADC_Joy_Start();
    UART_LOG_Start();
    PWM_1_Start();
    PWM_3_Start();
    PWM_1_WriteCompare(0);
    PWM_3_WriteCompare(0);
    UART_LOG_PutString("Hello User \r\n");
    stateMachine_init(); 
    MESSAGEBOX_INIT(&event_queue);
    TFT_init();
    //PONG_init_tft(&OO_PONG_MAIN);

    //Reconfigure ISRs with OS parameters.
    //This line MUST be called after the hardware driver initialisation!
    EE_system_init();
	
    //Start SysTick
	//Must be done here, because otherwise the isr vector is not overwritten yet
    EE_systick_start();  
	
    //Start the alarm with 100ms cycle time
    SetRelAlarm(alm_1ms,100,1);
    SetRelAlarm(alm_50ms,150,50);
    

    ActivateTask(tsk_control);
    ActivateTask(tsk_input);
    ActivateTask(tsk_hmi);
    
    TerminateTask();
    
}



/********************************************************************************
 * ISR Definitions
 ********************************************************************************/

/* [] END OF FILE */
