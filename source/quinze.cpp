#include <iostream>
#include <ncurses.h>

#include "quinze.hpp"
#include "display.hpp"
#include "settings.hpp"

void print_build_details(const settings& s)
{
  std::cout << "Quinze v" << s.version << std::endl;
  std::cout << "Copyright " << s.copyright_year << ", " << s.author;
  std::cout << std::endl << std::endl;
}

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

void quinze_loop(settings& set)
{
  bool keep_playing = true;

  while (keep_playing)
  {
    refresh_settings(set);

    clear_display();
    display_header(set);
    display_puzzle();
    display_footer(set);
    refresh_display();
    
    keep_playing = process_input();
  }  
}

void farewell()
{
  std::cout << "Thanks for playing!" << std::endl;
}

void quinze()
{
  settings set = get_settings();
  
  print_build_details(set);
  display_setup();
  quinze_loop(set);
  display_teardown();
  farewell();
}

int main()
{
  quinze();
}
