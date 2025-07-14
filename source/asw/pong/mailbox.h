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

#include "global.h"
#define MBSIZE 100
typedef enum {
    MB_TYPE_EVENTSIGNAL,
    MB_TYPE_HMI_GAME_SIGNAL,
    MB_TYPE_HMI_MENUE_SIGNAL,
    MB_TYPE_HMI_PAUSE_SIGNAL,
    MB_TYPE_NONE,
}MESSAGEBOX_type_t;

typedef struct {
    void * buffer;
    uint16_t buffer_size;
    MESSAGEBOX_type_t type;
} global_messagebox_buffer_t;

typedef struct {
    uint16_t fillLevel;
    uint16_t readIndex;
    uint16_t writeIndex;
    uint16_t size;
    global_messagebox_buffer_t messagebox_buffer[MBSIZE];
} MESSAGEBOX_t;

MESSAGEBOX_t event_queue;
MESSAGEBOX_t hmi_messagebox;

RC_t MESSAGEBOX_INIT(MESSAGEBOX_t* messagebox_data);
RC_t MESSAGEBOX_PUT(MESSAGEBOX_t* messagebox_data, void const * const buffer_data, MESSAGEBOX_type_t type, uint16_t size);
RC_t MESSAGEBOX_GET(MESSAGEBOX_t* messagebox_data, void * output_data, uint16_t size);

RC_t MESSAGEBOX_PEEK(MESSAGEBOX_t* box, MESSAGEBOX_type_t* type_out, uint16_t* size_out);
/* [] END OF FILE */
