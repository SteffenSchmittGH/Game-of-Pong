
/*
 * Filename: sc_pong_type.h
 *
 * Author: Autogenerated by H-DA RTE Generator, (c) Prof. Fromm
 */

#ifndef _H_DEFINE_SC_PONG_TYPE
#define _H_DEFINE_SC_PONG_TYPE

#include "project.h"
#include "global.h"
#include "rte_types.h"

/* USER CODE START SC_PONG_INCLUDES */
#include "debug_rte.h"
/* USER CODE END SC_PONG_INCLUDES */



/**********************************************************************
 *       Type Definition for SC_PONG signal    
 **********************************************************************/

/* USER CODE START SC_PONG_USERDEFINITIONS */
typedef struct {
    uint16_t y_position; // vertical
    uint16_t x_position; // horizontal
    uint16_t y_pos_old;
    uint16_t x_pos_old;
    uint16_t velocity;
    uint8_t direction;
}PONG_BAT_t;
//Game Object: META
typedef struct {
    uint8_t score;
    uint8_t round;
    uint8_t lifes;
}PONG_META_t;
//Game Object: BALL
/*
* direction is pos for upwards
* and neg for downwards.
*/
typedef struct {
    uint16_t y_position; //vertical
    uint16_t x_position; //horizontal
    uint16_t y_pos_old;
    uint16_t x_pos_old;
    uint16_t velocity;
    uint8_t direction; //UP: TRUE, DOWN: FALSE
}PONG_BALL_t;
//Game Object 
typedef struct {
    PONG_BAT_t bat_1;
    PONG_BAT_t bat_2;
    PONG_META_t meta;
    PONG_BALL_t ball;
}PONG_GAME_t;
/* USER CODE END SC_PONG_USERDEFINITIONS */

typedef 
/* USER CODE START SC_PONG_SIGNALDATADEFINITION */
struct
{
    boolean_t clear_screen;
    uint16_t menue_curser_pos;
	PONG_GAME_t game;
} 
/* USER CODE END SC_PONG_SIGNALDATADEFINITION */
SC_PONG_data_t;

/* USER CODE START InitSC_PONG */

/* USER CODE START InitSC_PONG */
#define SC_PONG_INIT_DATA ((SC_PONG_data_t){                                      \
    .clear_screen = FALSE,                                                       \
    .menue_curser_pos = 50,                                                      \
    .game = {                                                                     \
        .bat_1 = {                                                                \
            .y_position = BAT_Y_START_POSITION,                                   \
            .x_position = LIMIT_X_HORIZONTAL_TFT_MAX,                             \
            .y_pos_old = BAT_Y_START_POSITION,                                    \
            .x_pos_old = LIMIT_X_HORIZONTAL_TFT_MAX,                              \
            .velocity = 0,                                                        \
            .direction = 0                                                        \
        },                                                                        \
        .bat_2 = {                                                                \
            .y_position = BAT_Y_START_POSITION,                                   \
            .x_position = LIMIT_X_HORIZONTAL_TFT_MIN,                             \
            .y_pos_old = BAT_Y_START_POSITION,                                    \
            .x_pos_old = LIMIT_X_HORIZONTAL_TFT_MIN,                              \
            .velocity = 0,                                                        \
            .direction = 0                                                        \
        },                                                                        \
        .meta = {                                                                 \
            .score = 0,                                                           \
            .round = 0,                                                           \
            .lifes = 0                                                            \
        },                                                                        \
        .ball = {                                                                 \
            .y_position = BALL_Y_START_POSITION,                                  \
            .x_position = BALL_X_START_POSITION,                                  \
            .y_pos_old = BALL_Y_START_POSITION,                                   \
            .x_pos_old = BALL_X_START_POSITION,                                   \
            .velocity = 0,                                                        \
            .direction = 0                                                        \
        }                                                                         \
    }                                                                             \
})
/* USER CODE END InitSC_PONG */

/* USER CODE END InitSC_PONG */





/* USER CODE START SC_PONG_USERFUNCTIONS */

/* USER CODE END SC_PONG_USERFUNCTIONS */


#endif