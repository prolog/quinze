#include <iostream>
#include <ncurses.h>

#include "quinze.hpp"
#include "display.hpp"

void quinze_loop()
{
  getch();
}

void quinze()
{
  display_setup();
  quinze_loop();
  display_teardown();
}

int main()
{
  quinze();
}
