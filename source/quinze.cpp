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

void slide_tiles(state& st)
{
  shift_list shifts = get_shift_list(st.board, st.curs);
  
  if (!shifts.empty())
  {
    for (const auto& sh_p : shifts)
    {
      coord p = sh_p.first;
      st.board[p.first][p.second] = sh_p.second;
    }

    st.curs = shifts.at(shifts.size()-1).first;
  }
}

void check_winner(state& st)
{
  if (is_winner(st.board))
  {
    st.winner = true;
  }
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

void process_input(const settings& set, state& st, bool& keep_playing)
{
  int input = getch();

  if (input == 'q' || input == 'Q')
  {
    keep_playing = st.winner ? false : display_quit_prompt(set);
  }
  else if (is_movement(input) && !st.winner)
  {
    process_movement_input(st, input);
  }
  else if (!st.winner)
  {
    slide_tiles(st);
  }
}

void quinze_loop(settings& set, state& st)
{
  bool keep_playing = true;

  while (keep_playing)
  {
    refresh_settings(set);

    clear_display();
    display_header(set, st);
    display_puzzle(set, st);
    display_footer(set, st);
    refresh_display();
    
    process_input(set, st, keep_playing);
    check_winner(st);
  }  
}

void farewell(const settings& set, const state& st)
{
  std::string message = st.winner ? set.farewell_winner : set.farewell;
  std::cout << message  << std::endl;
}

void quinze()
{
  settings set = get_settings();
  state st = create_new_game();
  
  print_build_details(set);
  display_setup();
  quinze_loop(set, st);
  display_teardown();
  farewell(set, st);
}

int main()
{
  quinze();
}
