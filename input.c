#include <curses.h>
#include <stdbool.h>

void init_input() {
  initscr();
  cbreak();
  noecho();
  keypad(stdscr, true);
}

void deinit_input() {
  endwin();
}

