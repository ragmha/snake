#ifndef _GAME_H_
#define _GAME_H_

#include <ncurses.h>
#include <stdlib.h>
#include <time.h>

#define TICKRATE 150
#define WORLD_WIDTH 50
#define WORLD_HEIGHT 20
#define SNAKE_MAX_LENGTH 40
#define SNAKE_MIN_LENGTH 5

enum direction {UP, DOWN, RIGHT, LEFT};
enum gamestate {PLAY, PAUSE, LOST};
int gameState;

typedef struct{
  int x;
  int y;
} Food;

typedef struct{
  int x;
  int y;
} snakePart;

typedef struct {
  int curSnakeLength;
  snakePart body[SNAKE_MAX_LENGTH];
} Snake;


int  checkCollision(Snake *snake);
int  setupSnake(Snake* snake, int begX, int begY);
int  updateSnakePos(Snake *snake, int direction);
void growSnake(Snake *snake);
int  updateScreen(WINDOW *win, Snake *snake, int direction, Food *byte);
int  updateMenu(WINDOW *menu, int message);
void setFoodCoord(Snake *snake, Food *byte);
int  checkAteFood(Snake *snake, Food *byte);

#endif
