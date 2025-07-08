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
#include "inttypes.h"
#include "global.h"

typedef void (*StateAction)(void); // Correct definition of function pointer type
typedef int (*StateGuard)(void); // Correct definition of function pointer type

#define NUMBER_EVENTS 6
//events
typedef enum {
    EV_B1,
    EV_B2,
    EV_B3,
    EV_B4,
    EV_JOY_UP,
    EV_JOY_DOWN,
} CUSTOM_EVENTS;
//Container States, innerTransitionTable, outerTransitionsTable
typedef enum {
    PONG_C_PAUSE,
    PONG_C_MENUE,
    PONG_C_GAME,
}STATE_ContainerState_t;

typedef struct {
    CUSTOM_EVENTS event;
    STATE_ContainerState_t toState;
    StateGuard guard;
    StateAction action;
} STATE_innerTransition_Container_t;

typedef struct {
       STATE_ContainerState_t fromState;
       STATE_innerTransition_Container_t const * const pInnerTransitionTable;
       uint16_t size;
} STATE_outerTransition_Container_t;

typedef struct {
    STATE_ContainerState_t state;
    StateAction entry;
    StateAction exit;
    uint16_t size;
} STATE_stateAction_Container_t;

typedef enum {
    PONG_W_BAT_MOVE_UP,
    PONG_W_BAT_MOVE_DOWN,
    PONG_W_BAT_NO_MOVE,
}STATE_WidgetState_t;

typedef struct {
    CUSTOM_EVENTS event;
    STATE_WidgetState_t toState;
    StateGuard guard;
    StateAction action;
} STATE_innerTransition_Widget_t;

typedef struct {
       STATE_WidgetState_t fromState;
       STATE_innerTransition_Widget_t const * const pInnerTransitionTable;
       uint16_t size;
} STATE_outerTransition_Widget_t;

typedef struct {
    STATE_WidgetState_t state;
    StateAction entry;
    StateAction exit;
    uint16_t size;
} STATE_stateAction_Widget_t;

//active objects
typedef struct {
    STATE_outerTransition_Container_t const *  transitionTable;
    uint16_t transitionTableSize;
    STATE_stateAction_Container_t const * actionTable;
    STATE_ContainerState_t state;
} STATEMACHINE_Container_t;

typedef struct {
    STATE_outerTransition_Widget_t const *  transitionTable;
    uint16_t transitionTableSize;
    STATE_stateAction_Widget_t const * actionTable;
    STATE_WidgetState_t state;
} STATEMACHINE_Widget_t;

STATEMACHINE_Container_t sm_container_active;
STATEMACHINE_Widget_t sm_widget_active;


void stateMachine_init();
RC_t processEvent_Container(STATEMACHINE_Container_t * me, CUSTOM_EVENTS ev);
RC_t processEvent_Widget(STATEMACHINE_Widget_t * me, CUSTOM_EVENTS ev);

sint16_t getIndexOfTableByState_Container(STATE_outerTransition_Container_t const *const table, uint16_t size, STATE_ContainerState_t state);
sint16_t getIndexOfTableByState_Widget(STATE_outerTransition_Widget_t const *const table, uint16_t size, STATE_WidgetState_t state);

int b_dummy();
void  dummy();

void PONG__dispatch_B3_game();
void PONG__dispatch_B4_game();
void PONG__dispatch_JOYDOWN_game();
void PONG__dispatch_JOYUP_game();
void PONG_entry_show_pause();
void PONG_entry_show_menue();
void PONG_entry_move_up();
void PONG_entry_move_down();
/* [] END OF FILE */
