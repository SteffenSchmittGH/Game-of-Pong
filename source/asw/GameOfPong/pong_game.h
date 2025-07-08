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
//Game Object
//Game Object: BAT
/*
* direction is pos for upwards
* and neg for downwards.
*/
//OBJECT DEFINITIONS//
typedef struct {
    uint16_t y_position; // vertical
    uint16_t x_position; // horizontal
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
//Menue Object
typedef struct {
    char const * const menue_text;
}PONG_MENUE_t;
//Pause Object
typedef struct {
    char const * const pause_text;
}PONG_PAUSE_t;
//Global PONG Object
typedef struct {
    PONG_GAME_t game;
    PONG_MENUE_t menue;
    PONG_PAUSE_t pause;
}PONG_t;

typedef enum {
    PONG_GAME,
    PONG_PAUSE,
    PONG_MENUE,
}PONG_SETTINGS_t;

//GLOBAL OBJECTS//
extern PONG_MENUE_t OO_PONG_MENUE;
extern PONG_PAUSE_t OO_PONG_PAUSE;
PONG_t OO_PONG_MAIN;

//Setters and Getters//
//Setters and Getters: BAT
//BAT: pos
void set_bat_1_xy_position(PONG_t * pong, uint16_t xPos, uint16_t yPos);
uint16_t get_bat_1_x_pos(PONG_t * pong);
uint16_t get_bat_1_y_pos(PONG_t * pong);
//BAT: velocity
void set_bat_1_velocity(PONG_t * pong, uint16_t velocity);
uint16_t get_bat_1_velocity(PONG_t * pong);
//BAT: direction
void set_bat_1_direction(PONG_t * pong, uint8_t direction);
uint16_t get_bat_1_direction(PONG_t * pong);
//bat2
void set_bat_2_xy_position(PONG_t * pong, uint16_t xPos, uint16_t yPos);
uint16_t get_bat_2_x_pos(PONG_t * pong);
uint16_t get_bat_2_y_pos(PONG_t * pong);
//BAT: velocity
void set_bat_2_velocity(PONG_t * pong, uint16_t velocity);
uint16_t get_bat_2_velocity(PONG_t * pong);
//BAT: direction
void set_bat_2_direction(PONG_t * pong, uint8_t direction);
uint16_t get_bat_2_direction(PONG_t * pong);
//Setters and Getters: BALL
void set_ball_xy_position(PONG_t * pong, uint16_t xPos, uint16_t yPos);
uint16_t get_ball_x_pos(PONG_t * pong);
uint16_t get_ball_y_pos(PONG_t * pong);
//BAT: velocity
void set_ball_velocity(PONG_t * pong, uint16_t velocity);
uint16_t gell_bat_velocity(PONG_t * pong);
//BAT: direction
void set_ball_direction(PONG_t * pong, uint8_t direction);
uint16_t get_ball_direction(PONG_t * pong);
//Setters and Getters: META
//META: Score
void set_meta_score(PONG_t * pong, uint8_t score);
uint8_t get_meta_score(PONG_t * pong);
//META: Lifes
void set_meta_lifes(PONG_t * pong, uint8_t lifes);
uint8_t get_meta_lifes(PONG_t * pong);
//META: Round
void set_meta_round(PONG_t * pong, uint8_t round);
uint8_t get_meta_round(PONG_t * pong);
//Get Pause or Menue Text(setting is either pause or menue)
void get_screen_Text(PONG_t * pong, PONG_SETTINGS_t setting, char* status);



//init function for GAME
void PONG_GAME_init(PONG_t * pong);
//MAIN FUNCTION: PLAY THE GAME
void run(PONG_t * pong);


//tft update
void PONG_init_tft(PONG_t * game_init);
void PONG_update_tft_game(PONG_GAME_t * game);
void PONG_update_tft_pause(PONG_PAUSE_t * pause);
void PONG_update_tft_menue(PONG_MENUE_t * menue);
/* [] END OF FILE */
