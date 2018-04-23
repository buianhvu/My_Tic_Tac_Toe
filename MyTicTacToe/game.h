#ifndef GAME_H_
#define GAME_H_

#define N 3
#define MAX_WIDTH 860
#define MAX_HEIGHT 600
#define SCREEN_WIDTH MAX_WIDTH*0.75 //640
#define SCREEN_HEIGHT 480

#define EMPTY 0
#define PLAYER_X 1
#define PLAYER_O 2

#define RUNNING_STATE 0
#define PLAYER_X_WON_STATE 1
#define PLAYER_O_WON_STATE 2
#define TIE_STATE 3
#define QUIT_STATE 4
#define WELCOME_STATE 5

#define CELL_WIDTH (SCREEN_WIDTH/N)
#define CELL_HEIGHT (SCREEN_HEIGHT/N)

typedef struct {
	int board[N * N];
	int player;
	
	int state;
}game_t;
#endif // GAME_H_


