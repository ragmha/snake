#include "menus.h"

// Displays Initial Menu
void initMenu(WINDOW *win){
  //clear window
  wclear(win);

  //create window
  wattron(win, A_BOLD);
  box(win, 0, 0);
  //displayLogo(win);

  //set white for text
  init_pair(5, COLOR_WHITE, COLOR_BLACK);
  wattron(win, COLOR_PAIR(5));
  mvwaddstr(win, 25, 55, "             1) Start game");
  mvwaddstr(win, 26, 55, "             2) Instructions");
  mvwaddstr(win, 27, 55, "             3) Highscores");
  mvwaddstr(win, 28, 55, "             4) Quit");

  //init colors
  wattron(win, COLOR_PAIR(1));
  wrefresh(win);
}

// Displays Instructions
void instructions(WINDOW *win){
  //clear window
  wclear(win);

  //create window
  wattron(win, A_BOLD);
  box(win, 0, 0);
  //displayLogo(win);

  //set white for text
  init_pair(5, COLOR_WHITE, COLOR_BLACK);
  wattron(win, COLOR_PAIR(5));
  mvwaddstr(win, 14, 2, "                              INSTRUCTIONS");
  mvwaddstr(win, 16, 2, "                              Control keys:");
  mvwaddstr(win, 17, 2, "                              ↑ - UP");
  mvwaddstr(win, 18, 2, "                              ↓ - DOWN");
  mvwaddstr(win, 19, 2, "                              ← - LEFT");
  mvwaddstr(win, 20, 2, "                              → - RIGHT");
  mvwaddstr(win, 21, 2, "                              p - PAUSE");
  mvwaddstr(win, 22, 2, "                              Press 'q' to leave this menu");

  //init color
  wattron(win, COLOR_PAIR(1));
  wrefresh(win);

  //wait until q is pressed
  char c;
  do{
    c = getchar();
  }while(c != 'q');
}
