#include <iostream>
#include <ncurses.h>

#include "quinze.hpp"
#include "display.hpp"

int process_input()
{
  int keep_playing = true;
  int input = getch();

  if (input == 'q' || input == 'Q')
  {
    keep_playing = false;
  }

  return keep_playing;
}

void quinze_loop()
{
  bool keep_playing = true;

  while (keep_playing)
  {
    display_header();
    display_puzzle();
    display_footer();

    keep_playing = process_input();
  }  
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
