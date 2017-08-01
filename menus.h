#ifndef _MENUS_H_
#define _MENUS_H_

#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h>
#include <time.h>

void initMenu(WINDOW *win);
void instructions(WINDOW *win);
void finalMenu(WINDOW *win, int length);
void displayHighScore(WINDOW *win);
void pauseSubMenu(WINDOW *win);
void unpauseSubMenu(WINDOW *win);
void highScoreOrder(char num[], float score);
void displayHighScoreSubMenu(WINDOW *win);
void displayCurrentScoreSubMenu(WINDOW *win, float score);
void displayLogo(WINDOW *win);
void displaySnake(WINDOW *win);

#endif
