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
#include "mailbox.h"
#include "stdlib.h"
#include "UART_LOG.h"
#include "project.h"
#include "debug_rte.h"

#define MESSAGE_BOX_SIZE 100
RC_t MESSAGEBOX_INIT(MESSAGEBOX_t* messagebox_data)
{
    RC_t ret = RC_SUCCESS;
    messagebox_data->fillLevel = 0;
    for(int i = 0; i < MESSAGE_BOX_SIZE; i++)
    {
        messagebox_data->messagebox_buffer[i].buffer = NULL;
        messagebox_data->messagebox_buffer[i].buffer_size = 0;
        messagebox_data->messagebox_buffer[i].type = MB_TYPE_NONE;
    }
    messagebox_data->writeIndex = 0;
    messagebox_data->readIndex = 0;
    
    return ret;
}


RC_t MESSAGEBOX_PUT(MESSAGEBOX_t* messagebox_data, void const * const buffer_data, MESSAGEBOX_type_t type, uint16_t size )
{
    RC_t ret = RC_SUCCESS;
    #if MONITOR_FILL_LEVEL
        char buf[10];
        itoa(messagebox_data->fillLevel,buf,10);
        if(messagebox_data->messagebox_buffer[messagebox_data->writeIndex].type == MB_TYPE_EVENTSIGNAL)
        {
            UART_LOG_PutString("FL_W_E: ");
            UART_LOG_PutString(buf);
            UART_LOG_PutString("\r\n");
        }
        else if(messagebox_data->messagebox_buffer[messagebox_data->writeIndex].type == MB_TYPE_HMI_GAME_SIGNAL)
        {
            UART_LOG_PutString("FL_W_HMI: ");
            UART_LOG_PutString(buf);
            UART_LOG_PutString("\r\n");
        }
    #endif
    if(messagebox_data->fillLevel > MESSAGE_BOX_SIZE)
    {
        //UART_LOG_PutString("BUFFER_FULL\r\n");
        return RC_ERROR_BUFFER_FULL;   
    }
    //UART_LOG_PutString("MESSAGE BOX PUT\r\n");
    void * local_buffer = malloc(size);
    if(local_buffer == NULL || buffer_data == 0)
    {
        UART_LOG_PutString("BAD PARAM\r\n");
        return RC_ERROR_BAD_PARAM;
        //ret = RC_ERROR_BAD_PARAM;
    }
    
    uint8_t * src = (uint8_t*)buffer_data;
    uint8_t * dst = (uint8_t*)local_buffer;
    for(int i = 0; i <= size; i++)
    {
        dst[i] = src[i]; 
    }
    if(local_buffer != NULL)
    {
        GetResource(res_messagebox_fillLevel);
        messagebox_data->messagebox_buffer[messagebox_data->writeIndex].type = type;
        messagebox_data->messagebox_buffer[messagebox_data->writeIndex].buffer = local_buffer;
        messagebox_data->writeIndex = ( messagebox_data->writeIndex + 1) % MESSAGE_BOX_SIZE;
        messagebox_data->fillLevel++;
        ReleaseResource(res_messagebox_fillLevel);
        messagebox_data->messagebox_buffer[messagebox_data->writeIndex].buffer_size = size;
        messagebox_data->size = sizeof(*messagebox_data);
    }
    else
    {
        ret = RC_ERROR_MEMORY;   
    }
    return ret;
}

RC_t MESSAGEBOX_GET(MESSAGEBOX_t* messagebox_data, void * output_data, uint16_t size)
{
    #if MONITOR_FILL_LEVEL
        char buf[10];
        itoa(messagebox_data->fillLevel,buf,10);
        if(messagebox_data->messagebox_buffer[messagebox_data->readIndex].type == MB_TYPE_EVENTSIGNAL)
        {
            UART_LOG_PutString("FL_R_E: ");
            UART_LOG_PutString(buf);
            UART_LOG_PutString("\r\n");
        }
        else if(messagebox_data->messagebox_buffer[messagebox_data->readIndex].type == MB_TYPE_HMI_GAME_SIGNAL)
        {
            UART_LOG_PutString("FL_R_HMI: ");
            UART_LOG_PutString(buf);
            UART_LOG_PutString("\r\n");
        }
    #endif
    #if MONITOR_TYPE
        if(messagebox_data->messagebox_buffer[messagebox_data->readIndex].type == MB_TYPE_EVENTSIGNAL)
        {
            UART_LOG_PutString("EVENT\r\n");
        }
        else if(messagebox_data->messagebox_buffer[messagebox_data->readIndex].type == MB_TYPE_HMI_GAME_SIGNAL)
        {
            UART_LOG_PutString("HMI\r\n");
        }
        else if(messagebox_data->messagebox_buffer[messagebox_data->readIndex].type == MB_TYPE_HMI_MENUE_SIGNAL)
        {
            UART_LOG_PutString("HMI\r\n");
        }
        else if(messagebox_data->messagebox_buffer[messagebox_data->readIndex].type == MB_TYPE_HMI_PAUSE_SIGNAL)
        {
            UART_LOG_PutString("HMI\r\n");
        }
        else if(messagebox_data->messagebox_buffer[messagebox_data->readIndex].type == MB_TYPE_NONE)
        {
            UART_LOG_PutString("NONE\r\n");
        }
    #endif
    if(messagebox_data->fillLevel < 1)
    {
        return RC_ERROR_BUFFER_EMTPY;   
    }
    uint8_t* src = (uint8_t*)messagebox_data->messagebox_buffer[messagebox_data->readIndex].buffer;
    uint8_t* dst = (uint8_t*)output_data;
    
    for(int i = 0; i <= size; i++)
    {
        dst[i] = src[i];   
    }
    GetResource(res_messagebox_fillLevel);
    free(messagebox_data->messagebox_buffer[messagebox_data->readIndex].buffer);
    messagebox_data->messagebox_buffer[messagebox_data->readIndex].buffer = NULL;
    messagebox_data->messagebox_buffer[messagebox_data->readIndex].type = MB_TYPE_NONE;
    messagebox_data->messagebox_buffer[messagebox_data->readIndex].buffer_size = 0;
    messagebox_data->readIndex = (messagebox_data->readIndex + 1) % MESSAGE_BOX_SIZE; //critical resource
    messagebox_data->fillLevel = messagebox_data->fillLevel - 1; //critical resource
    ReleaseResource(res_messagebox_fillLevel);
    messagebox_data->size = sizeof(*messagebox_data);
    
    return RC_SUCCESS;
}

RC_t MESSAGEBOX_PEEK(MESSAGEBOX_t* box, MESSAGEBOX_type_t* type_out, uint16_t* size_out)
{
    RC_t ret = RC_SUCCESS;

    GetResource(res_messagebox_fillLevel);
    if (box->fillLevel < 1) {
        *type_out = MB_TYPE_NONE;
        *size_out = 0;
        ret = RC_ERROR_BUFFER_EMTPY;
    } else {
        *type_out = box->messagebox_buffer[box->readIndex].type;
        *size_out = box->messagebox_buffer[box->readIndex].buffer_size;
    }
    ReleaseResource(res_messagebox_fillLevel);
    return ret;
}

/* [] END OF FILE */
