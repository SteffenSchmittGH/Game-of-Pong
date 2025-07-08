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
#include "statemachine.h"
#include "stdlib.h"
#include "project.h"
#include "pong_game.h"
#include "mailbox.h"
//#include "rte.h"
//#include "rte_types.h"
//#include "sp_common.h"
#include "debug_rte.h"

//////////////////////////////CONTAINER STATEMACHINE //////////////////////////////////////////////////////////////
/*    EVENT                   TO_STATE                   GUARD         TRANSITIONACTION*/
const STATE_innerTransition_Container_t STATE_PONG_GAME_Transitions[] = { 
    { EV_JOY_UP,              PONG_C_GAME,               b_dummy,         PONG__dispatch_JOYUP_game},
    { EV_JOY_DOWN,            PONG_C_GAME,               b_dummy,         PONG__dispatch_JOYDOWN_game},
    { EV_B1,                  PONG_C_PAUSE,              b_dummy,         dummy},
    { EV_B2,                  PONG_C_MENUE,              b_dummy,         dummy},
    { EV_B4,                  PONG_C_GAME,               b_dummy,         PONG__dispatch_B4_game},
    { EV_B3,                  PONG_C_GAME,               b_dummy,         PONG__dispatch_B3_game},
};

/*    EVENT                   TO_STATE                   GUARD                          TRANSITIONACTION*/
const STATE_innerTransition_Container_t STATE_PONG_MENUE_Transitions[] = { 
    { EV_B3,                  PONG_C_GAME,                b_dummy,                       dummy},
    { EV_B2,                  PONG_C_PAUSE,               b_dummy,                       dummy},
};

/*    EVENT                   TO_STATE                   GUARD         TRANSITIONACTION*/
const STATE_innerTransition_Container_t STATE_PONG_PAUSE_Transitions[] = { 
    { EV_B1,                  PONG_C_GAME,                b_dummy,                       dummy},
    { EV_B2,                  PONG_C_MENUE,               b_dummy,                       dummy},
};

const STATE_outerTransition_Container_t PONG_Container_Transitions [] = { 
/*      FROM STATE                         INNER TABLE                                              SIZE  (inner)                                              */    
    {    PONG_C_GAME,                      &STATE_PONG_GAME_Transitions,                    sizeof(STATE_PONG_GAME_Transitions) / sizeof(STATE_innerTransition_Container_t)},
    {    PONG_C_MENUE,                     &STATE_PONG_MENUE_Transitions,                   sizeof(STATE_PONG_MENUE_Transitions) / sizeof(STATE_innerTransition_Container_t)},
    {    PONG_C_PAUSE,                     &STATE_PONG_PAUSE_Transitions,                    sizeof(STATE_PONG_PAUSE_Transitions) / sizeof(STATE_innerTransition_Container_t)},
};
const uint16_t CLOCK_Container_Transitions_Size = sizeof(PONG_Container_Transitions)/sizeof(STATE_outerTransition_Container_t);
/////////////// WIDGET STATEMACHINE /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const STATE_innerTransition_Widget_t STATE_PONG_W_BAT_UPWARDS_Transitions [] = {
    /*event                            toState                        Guard                           Action*/
    { EV_JOY_UP,                   PONG_W_BAT_MOVE_UP,                b_dummy,                        dummy},
    { EV_JOY_DOWN,                 PONG_W_BAT_MOVE_DOWN,              b_dummy,                        dummy},
};

const STATE_innerTransition_Widget_t STATE_PONG_W_BAT_DOWNWARDS_Transitions [] = {
        /*event                            toState                            Guard                       Action*/
    { EV_JOY_UP,                   PONG_W_BAT_MOVE_UP,                b_dummy,                        dummy},
    { EV_JOY_DOWN,                 PONG_W_BAT_MOVE_DOWN,              b_dummy,                        dummy},
};

const STATE_innerTransition_Widget_t STATE_PONG_W_BAT_NOMOVE_Transitions [] = { 
        /*event                            toState                    Guard                         Action*/
    { EV_JOY_UP,                   PONG_W_BAT_MOVE_UP,                b_dummy,                        dummy},
    { EV_JOY_DOWN,                 PONG_W_BAT_MOVE_DOWN,              b_dummy,                        dummy},
};

const STATE_outerTransition_Widget_t PONG_Widget_Transitions [] = {
        /*fromState                           PointerToTable                                      SIZE of Table [ELEMENTS]*/
    {    PONG_W_BAT_NO_MOVE,              &STATE_PONG_W_BAT_NOMOVE_Transitions,                    sizeof(STATE_PONG_W_BAT_NOMOVE_Transitions) / sizeof(STATE_innerTransition_Widget_t)},
    {    PONG_W_BAT_MOVE_UP,              &STATE_PONG_W_BAT_UPWARDS_Transitions,                   sizeof(STATE_PONG_W_BAT_UPWARDS_Transitions) / sizeof(STATE_innerTransition_Widget_t)},
    {    PONG_W_BAT_MOVE_DOWN,            &STATE_PONG_W_BAT_DOWNWARDS_Transitions,                 sizeof(STATE_PONG_W_BAT_DOWNWARDS_Transitions) / sizeof(STATE_innerTransition_Widget_t)},
};
const uint16_t CLOCK_Widget_Transitions_Size = sizeof(PONG_Widget_Transitions)/sizeof(STATE_outerTransition_Container_t);

STATE_stateAction_Container_t STATE_Actions_Entry_Exit_Container [] = { 
//       SATE                                      ENTRY                                                          EXIT        SIZE
    {PONG_C_MENUE,                      PONG_entry_show_menue,                                              dummy,                        1},
    {PONG_C_PAUSE,                      PONG_entry_show_pause,                                              dummy,                        1},
};

const STATE_stateAction_Widget_t STATE_Actions_Entry_Exit_Widget [] = { 
//SATE                                          ENTRY                                EXIT                         SIZE
    {PONG_W_BAT_MOVE_DOWN,                      PONG_entry_move_down,                  dummy,                        1},
    {PONG_W_BAT_MOVE_UP,                        PONG_entry_move_up,                    dummy,                        1},
};

void stateMachine_init(){
    sm_container_active.actionTable = STATE_Actions_Entry_Exit_Container;
    sm_container_active.state = PONG_C_MENUE; //Starting State
    sm_container_active.transitionTable = PONG_Container_Transitions;
    sm_container_active.transitionTableSize = CONTAINER_OUTER_TABLE_SIZE;
    
    sm_widget_active.actionTable = STATE_Actions_Entry_Exit_Widget;
    sm_widget_active.state = PONG_W_BAT_NO_MOVE; //Starting State
    sm_widget_active.transitionTable = PONG_Widget_Transitions;
    sm_widget_active.transitionTableSize = WIDGET_OUTER_TABLE_SIZE;
    
    return;
}

RC_t processEvent_Container(STATEMACHINE_Container_t * me, CUSTOM_EVENTS ev )
{
    RC_t ret = RC_SUCCESS;
    StateGuard guard = 0;
    StateAction acTransition = 0;
    StateAction acEntry = 0;
    StateAction acExit = 0;
    
    STATE_ContainerState_t currentState = me->state;
    STATE_ContainerState_t toState = currentState;
    
    //get index of outer table
    sint16_t index = getIndexOfTableByState_Container(me->transitionTable, me->transitionTableSize, currentState);
    #if  DEBUG_STATEMACHINE_INDEX
    UART_LOG_PutString("index: ");
    char buf[10];
    itoa(index ,buf,10);
    UART_LOG_PutString(buf);
    UART_LOG_PutString("\r\n");
    #endif
    //error Handling for index
    if(index == -1){
        UART_LOG_PutString("ERROR_RANGE_should_just occour when index is in undifined stater\r\n");
        return RC_ERROR_RANGE;   
    }
    //grep inner table through accessing outer table with index(maybe there is an more efficient way to calculate the index)
    STATE_innerTransition_Container_t const * const innerTransitionTable = me->transitionTable[index].pInnerTransitionTable; //möglicherweise pointer fehler!!!!!!!!!!!!!
    //getting innertable size in case prt is not 0
    uint16_t innerTableSize = 0;
    if(innerTransitionTable != 0){
        //UART_LOG_PutString("innerTransitionTable is not a null pointer \r\n");
           innerTableSize = me->transitionTable[index].size; //möglicherweise pointer fehler
    }
    //error handling if table or table size is zero
    if(innerTransitionTable == 0 || innerTableSize == 0){
       UART_LOG_PutString("some problems with innerTransitionTable\r\n");
        ret = RC_ERROR_ZERO;   
    }
    
    //iterate through inner table until event entry equals ev
    for(int i = 0; i < innerTableSize; i++){
        if(innerTransitionTable[i].event == ev){
            //UART_LOG_PutString("Event recognized within innerTransitionTable\r\n");
        //check if there is any Guard. Guard should be not nullpointer and should be TRUE
            if(innerTransitionTable[i].guard != NULL && innerTransitionTable[i].guard() == TRUE ){
                //UART_LOG_PutString("guard check passed\r\n");
                //guard passed:
                // check for TransitionAction to execute and update variable toState.
                acTransition = innerTransitionTable[i].action;
                toState = innerTransitionTable[i].toState;
                // now iterate through action Table and save entries where current state (exit) and toState (entry) fits.
                uint16_t actionTableSize = me->actionTable->size;
                for(int j = 0; j <= actionTableSize; j ++){
                    if(currentState == me->actionTable[j].state){
                        //UART_LOG_PutString("exit action found\r\n");
                        acExit = me->actionTable[j].exit;
                    }
                    if(toState == me->actionTable[j].state){
                       // UART_LOG_PutString("entry action found\r\n");
                        acEntry = me->actionTable[j].entry;
                    }
                }
                //execute in order exit, transition, entry7
                if(acExit != 0) acExit(); 
                //UART_LOG_PutString("C_Exit come back!\r\n");
                if(acTransition != 0) acTransition();
               // UART_LOG_PutString("Transition\r\n");
                if(acEntry != 0) acEntry();
                
               // UART_LOG_PutString("C_Entry come back!\r\n");
                
                //break; // if we just want to fire one transition
            }
        }
    }
    //Debug
    #if DEBUG_STATES 
    if(toState == PONG_C_GAME)
    {
        UART_LOG_PutString("PONG_C_GAME\r\n");
    }
    else if(toState == PONG_C_MENUE)
    {
        UART_LOG_PutString("PONG_C_MENUE\r\n");
    }
    else if(toState == PONG_C_PAUSE)
    {
        UART_LOG_PutString("PONG_C_PAUSE\r\n");
    }
    #endif
    // state change ???
    me->state = toState;
    return ret;
}

RC_t processEvent_Widget(STATEMACHINE_Widget_t * me, CUSTOM_EVENTS ev)
{
    RC_t ret = RC_SUCCESS;
    
    StateGuard guard = 0;
    StateAction acTransition = 0;
    StateAction acEntry = 0;
    StateAction acExit = 0;
    
    STATE_WidgetState_t currentState = me->state;
    STATE_WidgetState_t toState = currentState;
    
    //get index of outer table
    sint16_t index = getIndexOfTableByState_Widget(me->transitionTable, me->transitionTableSize, currentState);
    #if  DEBUG_STATEMACHINE_INDEX
    UART_LOG_PutString("index: ");
    char buf[10];
    itoa(index ,buf,10);
    UART_LOG_PutString(buf);
    UART_LOG_PutString("\r\n");
    #endif
    //error Handling for index
    if(index == -1){
        UART_LOG_PutString("ERROR_RANGE_should_just occour when index is in undifined stater\r\n");
        return RC_ERROR_RANGE;   
    }
    //grep inner table through accessing outer table with index(maybe there is an more efficient way to calculate the index)
    STATE_innerTransition_Widget_t const * const innerTransitionTable = me->transitionTable[index].pInnerTransitionTable; //möglicherweise pointer fehler!!!!!!!!!!!!!
    //getting innertable size in case prt is not 0
    uint16_t innerTableSize = 0;
    if(innerTransitionTable != 0){
        //UART_LOG_PutString("innerTransitionTable is not a null pointer \r\n");
           innerTableSize = me->transitionTable[index].size; //möglicherweise pointer fehler
    }
    //error handling if table or table size is zero
    if(innerTransitionTable == 0 || innerTableSize == 0){
        UART_LOG_PutString("some problems with innerTransitionTable\r\n");
        ret = RC_ERROR_ZERO;   
    }
    
    //iterate through inner table until event entry equals ev
    for(int i = 0; i < innerTableSize; i++){
        if(innerTransitionTable[i].event == ev){
            //UART_LOG_PutString("Event recognized within innerTransitionTable\r\n");
        //check if there is any Guard. Guard should be not nullpointer and should be TRUE
            if(innerTransitionTable[i].guard != NULL && innerTransitionTable[i].guard() == TRUE ){
                //UART_LOG_PutString("guard check passed\r\n");
                //guard passed:
                // check for TransitionAction to execute and update variable toState.
                acTransition = innerTransitionTable[i].action;
                //UART_LOG_PutString("found Transition Action\r\n");
                toState = innerTransitionTable[i].toState;
                // now iterate through action Table and save entries where current state (exit) and toState (entry) fits.
                uint16_t actionTableSize = me->actionTable->size;
                for(int j = 0; j <= actionTableSize; j ++){
                    if(currentState == me->actionTable[j].state){
                        //UART_LOG_PutString("exit action found\r\n");
                        acExit = me->actionTable[j].exit;
                        //UART_LOG_PutString("found Exit Action\r\n");
                    }
                    if(toState == me->actionTable[j].state){
                        //UART_LOG_PutString("entry action found\r\n");
                        acEntry = me->actionTable[j].entry;
                        //UART_LOG_PutString("found Entry Action\r\n");
                    }
                }
                //execute in order exit, transition, entry
                if(acExit != 0) acExit(); 
                //UART_LOG_PutString("W_Exit come back!\r\n");
                if(acTransition != 0) acTransition();
                //UART_LOG_PutString("W_Transition come back!\r\n");
                if(acEntry != 0) acEntry();
                //UART_LOG_PutString("W_Entry come back!\r\n");
                //break; // if we just want to fire one transition
            }
        }
    }
    // Debug
    #if DEBUG_STATES
    if(toState == PONG_W_BAT_MOVE_DOWN)
    {
        UART_LOG_PutString("PONG_W_BAT_MOVE_DOWN\r\n");
    }
    else if(toState == PONG_W_BAT_MOVE_UP)
    {
        UART_LOG_PutString("PONG_W_BAT_MOVE_UP\r\n");
    }
    else if(toState == PONG_W_BAT_NO_MOVE)
    {
        UART_LOG_PutString("PONG_W_BAT_NO_MOVE\r\n");
    }
    #endif
    // state change ???
    me->state = toState;
    return ret;
}


sint16_t getIndexOfTableByState_Container(STATE_outerTransition_Container_t const *const table, uint16_t size, STATE_ContainerState_t state){
    sint16_t indexOfState  = 0 ;
    boolean_t entryFound = FALSE;
    for(int i = 0;i < size; i++){
        if(table[i].fromState == state){
            indexOfState = i;
            entryFound = TRUE;
            break;
        }
    }
    if(!entryFound){
        indexOfState = -1;
    }
    return indexOfState;
}

sint16_t getIndexOfTableByState_Widget(STATE_outerTransition_Widget_t const *const table, uint16_t size, STATE_WidgetState_t state){
    sint16_t indexOfState  = 0 ;
    boolean_t entryFound = FALSE;
    for(int i = 0;i < size; i++){
        if(table[i].fromState == state){
            indexOfState = i;
            entryFound = TRUE;
            break;
        }
    }
    if(!entryFound){
        indexOfState = -1;
    }
    return indexOfState;
}


int b_dummy(){
    return 1;   
}

void dummy(){
    return;   
}

void PONG__dispatch_B3_game()
{
    processEvent_Widget(&sm_widget_active, EV_B3);
}

void PONG__dispatch_B4_game()
{
    processEvent_Widget(&sm_widget_active, EV_B4);
}

void PONG__dispatch_JOYDOWN_game()
{
    processEvent_Widget(&sm_widget_active, EV_JOY_DOWN);
}

void PONG__dispatch_JOYUP_game()
{
    processEvent_Widget(&sm_widget_active, EV_JOY_UP);
}

void PONG_entry_show_pause()
{
    //UART_LOG_PutString("PONG_entry_show_pause()\r\n");
    RC_t ret = MESSAGEBOX_PUT(&hmi_messagebox, (void*)&OO_PONG_PAUSE, MB_TYPE_HMI_PAUSE_SIGNAL, sizeof(OO_PONG_PAUSE)+1);
}

void PONG_entry_show_menue()
{
    //UART_LOG_PutString("PONG_entry_show_menue()\r\n");
    RC_t ret = MESSAGEBOX_PUT(&hmi_messagebox, (void*)&OO_PONG_MENUE, MB_TYPE_HMI_MENUE_SIGNAL, sizeof(OO_PONG_MENUE)+1);
}

void PONG_entry_move_up()
{
    uint16_t yPos = get_ball_y_pos(&OO_PONG_MAIN);
    uint16_t xPos;
    if(yPos < LIMIT_Y_VERTICAL_TFT_MAX)
    {
        UART_LOG_PutString("PONG_entry_move_up()\r\n");
        xPos = get_ball_x_pos(&OO_PONG_MAIN);
        yPos++;
        set_bat_1_xy_position(&OO_PONG_MAIN, xPos, yPos);
        set_bat_1_direction(&OO_PONG_MAIN,TRUE);  
        RC_t ret = MESSAGEBOX_PUT(&hmi_messagebox, (void*)&OO_PONG_MAIN, MB_TYPE_HMI_GAME_SIGNAL, sizeof(OO_PONG_MAIN) + 1);
    }
}

void PONG_entry_move_down()
{
    uint16_t yPos = get_ball_y_pos(&OO_PONG_MAIN);
    uint16_t xPos;
    if(yPos > LIMIT_Y_VERTICAL_TFT_MIN)
    {
        UART_LOG_PutString("PONG_entry_move_down()\r\n");
        xPos = get_ball_x_pos(&OO_PONG_MAIN);
        yPos--;
        set_bat_1_xy_position(&OO_PONG_MAIN, xPos, yPos);
        set_bat_1_direction(&OO_PONG_MAIN,FALSE);  
        RC_t ret = MESSAGEBOX_PUT(&hmi_messagebox, (void*)&OO_PONG_MAIN, MB_TYPE_HMI_GAME_SIGNAL,sizeof(OO_PONG_MAIN) + 1);
    }
}
/* [] END OF FILE */
