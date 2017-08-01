#include "main.h"

int main(){
  srand((unsigned int)time(NULL));

  // init screen
  WINDOW *snakeGame, *menuWin, *win = initscr();

  int offSetX, offSetY, menuOffSetY, ch;

  //initscr(); // start curses mode
  noecho();  // pressed characters not shown on the screen
  cbreak();  // typed character are read immedieatly without buffering
  timeout(TICKRATE);
  keypad(stdscr,true);
  curs_set(0); // hides the cursor

  initMenu(win);

  // refresh();

  offSetX = (COLS - WORLD_WIDTH)/2;
  offSetY = (LINES - WORLD_HEIGHT)/2;
  menuOffSetY = (offSetY - 4);

  snakeGame = newwin(WORLD_HEIGHT, WORLD_WIDTH, offSetY, offSetX);

  // Draw the Menu window
  menuWin = newwin(4, WORLD_WIDTH, menuOffSetY, offSetX);
  updateMenu(menuWin, 0);

  // Declare and Setup Sanke and Food
  Snake snake;
  Food byte;

  int sbegX = WORLD_WIDTH - (WORLD_WIDTH - SNAKE_MIN_LENGTH)/2 - 1;
  int sbegY = (WORLD_HEIGHT - 1)/2;

  setupSnake(&snake,sbegX, sbegY);
  setFoodCoord(&snake, &byte);

  // Setup game variable
  int curDirection = RIGHT;
  gameState = PLAY;

  while((ch = getch()) != 'x'){
    updateScreen(snakeGame, &snake, curDirection, &byte);

    switch(gameState){
      case PLAY:
        if(ch != ERR){
          switch(ch){
            case KEY_UP:
              if(curDirection != DOWN)
                curDirection = UP;
              break;

            case KEY_DOWN:
              if(curDirection != UP)
                curDirection = DOWN;
              break;

            case KEY_RIGHT:
              if(curDirection != LEFT)
                curDirection = RIGHT;
              break;

            case KEY_LEFT:
              if(curDirection != RIGHT)
                curDirection = LEFT;
              break;

            case 'p':
	      gameState = PAUSE;
	      break;

            case 'r':
              setupSnake(&snake, sbegX, sbegY);
              curDirection = RIGHT;
              break;

            default:
              break;
          }
        }

      case PAUSE:
        if(ch != ERR){
          switch(ch){
            case 'p':
              gameState = PLAY;
              break;
            case 'r':
              setupSnake(&snake, sbegX, sbegY);
              setFoodCoord(&snake, &byte);
              gameState = PLAY;
              curDirection = RIGHT;
              break;
            default:
              break;
          }
        }
        break;

      case LOST:
        updateMenu(menuWin, 1);

        if(ch != ERR){
          switch(ch){
            case 'r': // resets snake and screen
              updateMenu(menuWin, 0);
              setupSnake(&snake, sbegX, sbegY);
              setFoodCoord(&snake, &byte);
              gameState = PLAY;
              curDirection = RIGHT;
              break;
            default:
              break;
          }
        }
        break;

      default:
        break;
    }
  }

  delwin(snakeGame);
  endwin();
  return 0;
}
