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
#include "pong_game.h"
#include "tft.h"
#include "debug_rte.h"

PONG_MENUE_t OO_PONG_MENUE = {
    "MENUE"
};
PONG_PAUSE_t OO_PONG_PAUSE = {
    "PAUSE"
};

//BAT1: pos
void set_bat_1_xy_position(PONG_t * pong, uint16_t xPos, uint16_t yPos)
{
    pong->game.bat_1.x_position = xPos;
    pong->game.bat_1.y_position = yPos;
}

uint16_t get_bat_1_x_pos(PONG_t * pong)
{
    return pong->game.bat_1.x_position;
}

uint16_t get_bat_1_y_pos(PONG_t * pong)
{
    return pong->game.bat_2.y_position;
}

//BAT: velocity
void set_bat_1_velocity(PONG_t * pong, uint16_t velocity)
{
    pong->game.bat_1.velocity = velocity;
}

uint16_t get_bat_1_velocity(PONG_t * pong)
{
    return pong->game.bat_1.velocity;
}

//BAT: direction
void set_bat_1_direction(PONG_t * pong, uint8_t direction)
{
    pong->game.bat_1.direction = direction;
}

uint16_t get_bat_1_direction(PONG_t * pong)
{
    return pong->game.bat_1.direction;
}
//bat2
void set_bat_2_xy_position(PONG_t * pong, uint16_t xPos, uint16_t yPos)
{
    pong->game.bat_2.x_position = xPos;
    pong->game.bat_2.y_position = yPos;
}

uint16_t get_bat_2_x_pos(PONG_t * pong)
{
    return pong->game.bat_2.x_position;
}

uint16_t get_bat_2_y_pos(PONG_t * pong)
{
    return pong->game.bat_2.y_position;
}

//BAT: velocity
void set_bat_2_velocity(PONG_t * pong, uint16_t velocity)
{
    pong->game.bat_2.velocity = velocity;
}

uint16_t get_bat_2_velocity(PONG_t * pong)
{
    return pong->game.bat_2.velocity;
}

//BAT: direction
void set_bat_2_direction(PONG_t * pong, uint8_t direction)
{
    pong->game.bat_2.direction = direction;
}

uint16_t get_bat_2_direction(PONG_t * pong)
{
    return pong->game.bat_2.direction;
}
//Setters and Getters: BALL
void set_ball_xy_position(PONG_t * pong, uint16_t xPos, uint16_t yPos)
{
    pong->game.ball.y_position = yPos;
    pong->game.ball.x_position = xPos;
}

uint16_t get_ball_x_pos(PONG_t * pong)
{
    return pong->game.ball.x_position;
}

uint16_t get_ball_y_pos(PONG_t * pong)
{
    return pong->game.ball.y_position;
}

//BAT: velocity
void set_ball_velocity(PONG_t * pong, uint16_t velocity)
{
    pong->game.ball.velocity = velocity;
}

uint16_t gell_bat_velocity(PONG_t * pong)
{
    return pong->game.ball.velocity;
}

//BAT: direction
void set_ball_direction(PONG_t * pong, uint8_t direction)
{
    pong->game.ball.direction = direction;
}

uint16_t get_ball_direction(PONG_t * pong)
{
    return pong->game.ball.direction;
}

//META: Score
void set_meta_score(PONG_t * pong, uint8_t score)
{
    pong->game.meta.score = score;
}

uint8_t get_meta_score(PONG_t * pong)
{
    return pong->game.meta.score;
}

//META: Lifes
void set_meta_lifes(PONG_t * pong, uint8_t lifes)
{
    pong->game.meta.lifes = lifes;
}

uint8_t get_meta_lifes(PONG_t * pong)
{
    return pong->game.meta.lifes;
}

//META: Round
void set_meta_round(PONG_t * pong, uint8_t round)
{
    pong->game.meta.round = round;
}

uint8_t get_meta_round(PONG_t * pong)
{
    return pong->game.meta.round;
}
//Get Pause or Menue Text(setting is either pause or menue)
void get_screen_Text(PONG_t * pong, PONG_SETTINGS_t setting, char * status)
{
    if(setting == PONG_MENUE)
    {
        for(int i = 0; i <= 5; i++)
        {
            status[i] = pong->menue.menue_text[i];   
        }
    }
    else if(setting == PONG_PAUSE)
    {
        for(int i = 0; i <= 5; i++)
        {
            status[i] = pong->pause.pause_text[i];   
        }
    }
    return;
}



//init function for GAME
void PONG_GAME_init(PONG_t * pong)
{
    pong->game.bat_1.x_position = LIMIT_X_HORIZONTAL_TFT_MAX;
    pong->game.bat_2.x_position = LIMIT_X_HORIZONTAL_TFT_MIN;
    pong->game.bat_1.y_position = BAT_Y_START_POSITION;
    pong->game.bat_2.y_position = BAT_Y_START_POSITION;
    pong->game.ball.x_position = BALL_X_START_POSITION;
    pong->game.ball.y_position = BALL_Y_START_POSITION;
}
//MAIN FUNCTION: PLAY THE GAME
void run(PONG_t * pong)
{
    //ask position of ball
    //change position of ball into "direction"
    //ask if position is at wall, bat or something else and akt
}


void PONG_init_tft(PONG_t * game_init)
{
    TFT_init();
    PONG_GAME_init(game_init);
    TFT_fillRect(game_init->game.bat_1.y_position, game_init->game.bat_1.x_position, WIDTH_RECTANGLE, HIGHT_RECTANGLE, WHITE);
    TFT_fillRect(game_init->game.bat_2.y_position, game_init->game.bat_2.x_position, WIDTH_RECTANGLE, HIGHT_RECTANGLE, WHITE);
    TFT_fillCircle(game_init->game.ball.y_position, game_init->game.ball.x_position, BALL_RADIUS, WHITE);
}

void PONG_update_tft_game(PONG_GAME_t * game)
{
    TFT_fillRect(game->bat_1.y_position, game->bat_1.x_position, WIDTH_RECTANGLE, HIGHT_RECTANGLE, WHITE);
    TFT_fillRect(game->bat_2.y_position, game->bat_2.x_position, WIDTH_RECTANGLE, HIGHT_RECTANGLE, WHITE);
    TFT_fillCircle(game->ball.y_position, game->ball.x_position, BALL_RADIUS, WHITE);
}

void PONG_update_tft_pause(PONG_PAUSE_t * pause)
{
    TFT_println("PAUSE"); 
}

void PONG_update_tft_menue(PONG_MENUE_t * menue)
{
    TFT_println("MENUE");
}
/* [] END OF FILE */
