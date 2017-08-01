#include "game.h"

int setupSnake(Snake *snake, int begX, int begY)
{
  snake->curSnakeLength = SNAKE_MIN_LENGTH;
  int i;

  // setUp initial snake body position
  for (i = 0; i < SNAKE_MIN_LENGTH; i++)
  {
    snake->body[i].x = begX - i;
    snake->body[i].y = begY;
  }

  // set rest body values to 0
  for (; i < SNAKE_MIN_LENGTH; i++)
  {
    snake->body[i].x = 0;
    snake->body[i].y = 0;
  }

  return 0;
}

int updateScreen(WINDOW *win, Snake *snake, int direction, Food *byte)
{
  wclear(win);

  int i;
  int curSnakeLength = snake->curSnakeLength;

  if (gameState == PLAY)
  {
    updateSnakePos(snake, direction);
  }

  for (i = 1; i < curSnakeLength; i++)
  {
    //'mvwaddch'- add a character (with attributes) to a curses window
    mvwaddch(win, snake->body[i].y, snake->body[i].x, '#');
  }

  int collided = 0;

  // Check if Snake Ate Food
  if (checkAteFood(snake, byte) == 1)
  {
    mvwaddch(win, snake->body[0].y, snake->body[0].x, 'O');
    setFoodCoord(snake, byte);
    growSnake(snake);
    beep();
    collided = 1;
  }
  else
  {
    mvwaddch(win, byte->y, byte->x, '@');
  }

  // Check if player caused snake to collide with itself, Update games state
  if (checkCollision(snake) == 1)
  {
    mvwaddch(win, snake->body[0].y, snake->body[0].x, 'X');
    gameState = LOST;
    collided = 1;
  }

  if (!collided)
  {
    mvwaddch(win, snake->body[0].y, snake->body[0].x, '#');
  }

  box(win, 0, 0);
  wrefresh(win);
  return 0;
}

int updateSnakePos(Snake *snake, int direction)
{
  int i;
  int curSnakeLength = snake->curSnakeLength;

  for (i = curSnakeLength - 1; i > 0; i--)
  {
    snake->body[i] = snake->body[i - 1];
  }

  int x = snake->body[0].x;
  int y = snake->body[0].y;

  //Check direction and update cordinates accordingly
  switch (direction)
  {
  case UP:
    y - 1 == 0 ? y = WORLD_HEIGHT - 2 : y--;
    break;

  case DOWN:
    y + 1 == WORLD_HEIGHT - 1 ? y = 1 : y++;
    break;

  case RIGHT:
    x + 1 == WORLD_WIDTH - 1 ? x = 1 : x++;
    break;

  case LEFT:
    x - 1 == 0 ? x = WORLD_WIDTH - 2 : x--;
    break;

  default:
    break;
  }

  snake->body[0].x = x;
  snake->body[0].y = y;

  return 0;
}

void growSnake(Snake *snake)
{
  if (snake->curSnakeLength < SNAKE_MAX_LENGTH)
  {
    snake->curSnakeLength++;

    //new part cordinates is old part of snake
    int newPart = snake->curSnakeLength;
    snake->body[newPart] = snake->body[newPart - 1];
  }
}

int checkCollision(Snake *snake)
{
  int headX = snake->body[0].x;
  int headY = snake->body[0].y;

  int curLength = snake->curSnakeLength;
  int i;
  for (i = 1; i < curLength; i++)
  {
    if (snake->body[i].x == headX && snake->body[i].y == headY)
    {
      return 1;
    }
  }
  return 0;
}

int checkAteFood(Snake *snake, Food *byte)
{
  if (snake->body[0].x == byte->x && snake->body[0].y == byte->y)
  {
    return 1;
  }
  return 0;
}

int updateMenu(WINDOW *menu, int message)
{
  wclear(menu);
  switch (message)
  {
  case 1:
    wprintw(menu, "Game Over...\n Press x to quit, r to reset.\n");
    break;
  default:
    wprintw(menu, "Snake \n Press p to play/pause, x to quit, r to reset");
    break;
  }
  wrefresh(menu);
  return 0;
}

void setFoodCoord(Snake *snake, Food *byte)
{
  int clear = 1;
  int newX, newY;

  // Generate new coordinates for food
  do
  {
    if (clear == 0)
    {
      clear = 1;
    }
    newX = rand() % WORLD_WIDTH;
    newY = rand() % WORLD_HEIGHT;

    // Check if newX or newY are on the border of box
    // increments/decrements from the border
    if (newX == 0)
    {
      newX++;
    }
    else if (newX == 49)
    {
      newX--;
    }

    if (newY == 0)
    {
      newY++;
    }
    else if (newY == 29)
    {
      newY--;
    }

    int snakeLength = snake->curSnakeLength;
    int i;

    for (i = 0; i < snakeLength; i++)
    {
      if (snake->body[i].x == newX && snake->body[i].y == newY)
      {
        clear = 0;
      }
    }
  } while (clear != 1);

  byte->x = newX;
  byte->y = newY;
}
