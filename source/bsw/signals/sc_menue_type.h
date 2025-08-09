#ifndef _H_DEFINE_SC_MENUE_TYPE
#define _H_DEFINE_SC_MENUE_TYPE

#include "project.h"
#include "global.h"
#include "rte_types.h"

/* USER CODE START SC_MENUE_INCLUDES */

/* USER CODE END SC_MENUE_INCLUDES */



/**********************************************************************
 *       Type Definition for SC_MENUE signal    
 **********************************************************************/

/* USER CODE START SC_MENUE_USERDEFINITIONS */
#define NUMBER_OF_GAMES 3
typedef enum {
    GAMES_TYPE_PONG,
    GAMES_TYPE_SNAKE,
    GAMES_TYPE_SOCCER,
}GAMES_TYPES_t;
typedef enum {
    GAMES_SCREEN_PONG,
    GAMES_SCREEN_PAUSE,
    GAMES_SCREEN_MENUE,
    GAMES_SCREEN_NONE,
}GAMES_SCREEN_TYPES_t;
/* USER CODE END SC_MENUE_USERDEFINITIONS */

typedef 
/* USER CODE START SC_MENUE_SIGNALDATADEFINITION */
struct
{
    GAMES_SCREEN_TYPES_t games_current;
	GAMES_TYPES_t game_types[NUMBER_OF_GAMES];
    uint16_t types_index;
} 
/* USER CODE END SC_MENUE_SIGNALDATADEFINITION */
SC_MENUE_data_t;

/* USER CODE START InitSC_MENUE */
#define SC_MENUE_INIT_DATA ((SC_MENUE_data_t){GAMES_SCREEN_MENUE,{GAMES_TYPE_PONG,GAMES_TYPE_SNAKE,GAMES_TYPE_SOCCER},0})
/* USER CODE END InitSC_MENUE */





/* USER CODE START SC_MENUE_USERFUNCTIONS */

/* USER CODE END SC_MENUE_USERFUNCTIONS */


#endif
