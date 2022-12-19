#include <algorithm>
#include <iostream>
#include <ncurses.h>

#include "quinze.hpp"
#include "display.hpp"

void print_build_details(const settings& s)
{
  std::cout << "Quinze v" << s.version << std::endl;
  std::cout << "Copyright " << s.copyright_year << ", " << s.author;
  std::cout << std::endl << std::endl;
}

bool is_movement(const int input)
{
  std::vector<int> movement_vals = get_curs_inputs();

  return (std::find(movement_vals.begin(), movement_vals.end(), input) != movement_vals.end());
}

void process_movement_input(state& st, const int input)
{
  auto curs = get_next_curs(st.curs, input);

  if (curs != st.curs)
  {
    st.curs = curs;
  }
}

void process_input(state& st, bool& keep_playing)
{
  int input = getch();

  if (input == 'q' || input == 'Q')
  {
    keep_playing = false;
  }
  else if (is_movement(input))
  {
    process_movement_input(st, input);
  }
}

void quinze_loop(settings& set, state& st)
{
  bool keep_playing = true;

  while (keep_playing)
  {
    refresh_settings(set);

    clear_display();
    display_header(set);
    display_puzzle(set, st);
    display_footer(set);
    refresh_display();
    
    process_input(st, keep_playing);
  }  
}

void farewell()
{
  std::cout << "Thanks for playing!" << std::endl;
}

void quinze()
{
  settings set = get_settings();
  state st = create_new_game();
  
  print_build_details(set);
  display_setup();
  quinze_loop(set, st);
  display_teardown();
  farewell();
}

int main()
{
  quinze();
}
