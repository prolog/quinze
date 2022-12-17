#include "display.hpp"

void display_setup()
{
  initscr();
  curs_set(0);
  noecho();
}

void display_teardown()
{
  endwin();
}

void display_header()
{
}

void display_puzzle()
{
}

void display_footer()
{
}
