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

#include "mailbox.h"
//#include "rte.h"
//#include "rte_types.h"
#include "sp_common.h"
#include "debug_rte.h"
#include "games.h"

//////////////////////////////CONTAINER STATEMACHINE //////////////////////////////////////////////////////////////
/*    EVENT                   TO_STATE                   GUARD         TRANSITIONACTION*/
const STATE_innerTransition_Container_t STATE_GAMES_PONG_Transitions[] = { 
    { EV_JOY_UP,              GAMES_C_PONG,               b_dummy,         PONG__dispatch_JOYUP_pong},
    { EV_JOY_DOWN,            GAMES_C_PONG,               b_dummy,         PONG__dispatch_JOYDOWN_pong},
    { EV_B1,                  GAMES_C_PAUSE,              b_dummy,         dummy},
    { EV_B3,                  GAMES_C_MENUE,              b_dummy,         dummy},
    { EV_JOY_NONE,            GAMES_C_PONG,               b_dummy,         PONG__dispatch_JOYNONE_pong},
};

/*    EVENT                   TO_STATE                   GUARD                          TRANSITIONACTION*/
const STATE_innerTransition_Container_t STATE_GAMES_MENUE_Transitions[] = { 
    { EV_B3,                  GAMES_C_PONG,                PONG_pongSelected,             dummy},
    { EV_B1,                  GAMES_C_MENUE,               b_dummy,                       PONG_increaseCurserPos},
    { EV_B2,                  GAMES_C_MENUE,               b_dummy,                       PONG_decreaseCurserPos},
};

/*    EVENT                      TO_STATE                          GUARD                 TRANSITIONACTION*/
const STATE_innerTransition_Container_t STATE_GAMES_PAUSE_Transitions[] = { 
    { EV_B1,                  GAMES_C_PONG,                PONG_pongSelected,             dummy},
};

const STATE_outerTransition_Container_t GAMES_Container_Transitions [] = { 
/*      FROM STATE                         INNER TABLE                                              SIZE  (inner)                                              */    
    {    GAMES_C_PONG,                      &STATE_GAMES_PONG_Transitions,                    sizeof(STATE_GAMES_PONG_Transitions) / sizeof(STATE_innerTransition_Container_t)},
    {    GAMES_C_MENUE,                     &STATE_GAMES_MENUE_Transitions,                   sizeof(STATE_GAMES_MENUE_Transitions) / sizeof(STATE_innerTransition_Container_t)},
    {    GAMES_C_PAUSE,                     &STATE_GAMES_PAUSE_Transitions,                   sizeof(STATE_GAMES_PAUSE_Transitions) / sizeof(STATE_innerTransition_Container_t)},
};
const uint16_t CLOCK_Container_Transitions_Size = sizeof(GAMES_Container_Transitions)/sizeof(STATE_outerTransition_Container_t);
/////////////// WIDGET STATEMACHINE /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const STATE_innerTransition_Widget_t STATE_PONG_W_BAT_UPWARDS_Transitions [] = {
    /*event                            toState                        Guard                           Action*/
    { EV_JOY_UP,                   PONG_W_BAT_MOVE_UP,                b_dummy,                        dummy},
    { EV_JOY_DOWN,                 PONG_W_BAT_MOVE_DOWN,              b_dummy,                        dummy},
    { EV_JOY_NONE,                 PONG_W_BAT_NO_MOVE,                b_dummy,                        dummy},
};

const STATE_innerTransition_Widget_t STATE_PONG_W_BAT_DOWNWARDS_Transitions [] = {
        /*event                            toState                            Guard                       Action*/
    { EV_JOY_UP,                   PONG_W_BAT_MOVE_UP,                b_dummy,                        dummy},
    { EV_JOY_DOWN,                 PONG_W_BAT_MOVE_DOWN,              b_dummy,                        dummy},
    { EV_JOY_NONE,                 PONG_W_BAT_NO_MOVE,                b_dummy,                        dummy},
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
//       SATE                                      ENTRY                                                          EXIT                       SIZE
    {GAMES_C_PONG,                       PONG_set_isGame,                                                      dummy,                                   2},
    //{GAMES_C_MENUE,                      dummy,                                                                GAMES_clearScreen,                       4},
    {GAMES_C_MENUE,                      PONG_set_isMenue,                                                     GAMES_clearScreen,                       2},
    //{GAMES_C_PAUSE,                      dummy,                                                                GAMES_clearScreen,                       4},
    {GAMES_C_PAUSE,                      PONG_set_isPause,                                                     GAMES_clearScreen,                       2},                      
};

const STATE_stateAction_Widget_t STATE_Actions_Entry_Exit_Widget [] = { 
//SATE                                          ENTRY                                EXIT                         SIZE
    {PONG_W_BAT_MOVE_DOWN,                      PONG_entry_move_down,                  dummy,                        1},
    {PONG_W_BAT_MOVE_UP,                        PONG_entry_move_up,                    dummy,                        1},
};

void stateMachine_init(){
    sm_container_active.actionTable = STATE_Actions_Entry_Exit_Container;
    sm_container_active.state = GAMES_C_MENUE; //Starting State
    sm_container_active.transitionTable = GAMES_Container_Transitions;
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
    //StateGuard guard = 0;
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
    if(toState == GAMES_C_PONG)
    {
        UART_LOG_PutString("GAMES_C_PONG\r\n");
    }
    else if(toState == GAMES_C_MENUE)
    {
        UART_LOG_PutString("GAMES_C_MENUE\r\n");
    }
    else if(toState == GAMES_C_PAUSE)
    {
        UART_LOG_PutString("GAMES_C_PAUSE\r\n");
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

void PONG__dispatch_JOYNONE_pong()
{
    processEvent_Widget(&sm_widget_active, EV_JOY_NONE);
}

void PONG__dispatch_B3_pong()
{
    processEvent_Widget(&sm_widget_active, EV_B3);
}

void PONG__dispatch_JOYDOWN_pong()
{
    processEvent_Widget(&sm_widget_active, EV_JOY_DOWN);
}

void PONG__dispatch_JOYUP_pong()
{
    processEvent_Widget(&sm_widget_active, EV_JOY_UP);
}

void PONG_entry_move_up()
{
    SC_PONG_data_t game_data = RTE_SC_PONG_get(&SO_GAME_signal);
    uint16_t yPos = game_data.game.bat_1.y_position; //get_bat_1_y_pos(&OO_PONG_MAIN);
    uint16_t xPos;
    if(yPos < 120)
    {
        //game_data.game.bat_1.y_pos_old = yPos; //bat1_set_old_yPos(&OO_PONG_MAIN,yPos);
        yPos+=1;
        game_data.game.bat_1.y_position = yPos; //set_bat_1_xy_position(&OO_PONG_MAIN, xPos, yPos);
        game_data.game.bat_1.direction = TRUE; //set_bat_1_direction(&OO_PONG_MAIN,TRUE);  
    }
    RTE_SC_PONG_set(&SO_GAME_signal, game_data);
}

void PONG_entry_move_down()
{
    SC_PONG_data_t game_data = RTE_SC_PONG_get(&SO_GAME_signal);
    uint16_t yPos = game_data.game.bat_1.y_position;//get_bat_1_y_pos(&OO_PONG_MAIN);
    uint16_t xPos;
    if(yPos > 10)
    {
        //game_data.game.bat_1.y_pos_old = yPos;// bat1_set_old_yPos(&OO_PONG_MAIN,yPos);
        yPos-=1;
        game_data.game.bat_1.y_position = yPos;//set_bat_1_xy_position(&OO_PONG_MAIN, xPos, yPos);
        game_data.game.bat_1.direction = FALSE;  
    }
    RTE_SC_PONG_set(&SO_GAME_signal, game_data);
}

void PONG_set_isGame()
{
    SC_MENUE_data_t menue_data = RTE_SC_MENUE_get(&SO_MENUE_signal);
    menue_data.games_current = GAMES_SCREEN_PONG;
    RTE_SC_MENUE_set(&SO_MENUE_signal, menue_data);
}

void PONG_set_isPause()
{
    SC_MENUE_data_t menue_data = RTE_SC_MENUE_get(&SO_MENUE_signal);
    menue_data.games_current = GAMES_SCREEN_PAUSE;
    RTE_SC_MENUE_set(&SO_MENUE_signal, menue_data);
}

void PONG_set_isMenue()
{
    SC_MENUE_data_t menue_data = RTE_SC_MENUE_get(&SO_MENUE_signal);
    menue_data.games_current = GAMES_SCREEN_MENUE;
    RTE_SC_MENUE_set(&SO_MENUE_signal, menue_data);
}

int PONG_pongSelected()
{
    SC_MENUE_data_t menue_data = RTE_SC_MENUE_get( &SO_MENUE_signal );
    return (menue_data.game_types[menue_data.types_index] == GAMES_TYPE_PONG) ? 1 : 0;
}

void GAMES_clearScreen()
{
    SC_PONG_data_t game_data = RTE_SC_PONG_get(&SO_GAME_signal); 
    game_data.clear_screen = TRUE;
    RTE_SC_PONG_set(&SO_GAME_signal, game_data);
}

void PONG_increaseCurserPos()
{
    SC_PONG_data_t game_data = RTE_SC_PONG_get(&SO_GAME_signal);
    uint16_t pos = game_data.menue_curser_pos;//get_curser_pos();
    if(pos < 90)
    {
        pos+=CURSER_STEP;
        game_data.menue_curser_pos = pos; //set_curser_pos(pos);
        RTE_SC_PONG_set(&SO_GAME_signal, game_data);
    }
    SC_MENUE_data_t menue_data = RTE_SC_MENUE_get( &SO_MENUE_signal );
    if(menue_data.types_index != 1)
    {
        menue_data.types_index--;
        RTE_SC_MENUE_set(&SO_MENUE_signal, menue_data);
    }
}

void PONG_decreaseCurserPos()
{
    SC_PONG_data_t game_data = RTE_SC_PONG_get(&SO_GAME_signal);
    uint16_t pos = game_data.menue_curser_pos;//get_curser_pos();
    if(pos > 50)
    {
        pos-=CURSER_STEP;
        game_data.menue_curser_pos = pos;//set_curser_pos(pos);
        RTE_SC_PONG_set(&SO_GAME_signal, game_data);
    }
    SC_MENUE_data_t menue_data = RTE_SC_MENUE_get( &SO_MENUE_signal );
    if(menue_data.types_index != NUMBER_OF_GAMES)
    {
        menue_data.types_index++;
        RTE_SC_MENUE_set(&SO_MENUE_signal, menue_data);
    }
}
/* [] END OF FILE */
