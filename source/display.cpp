#include "display.hpp"

const int CURSES_NUM_TOTAL_COLOURS = 16;

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

void clear_display()
{
  clear();
}

void refresh_display()
{
  refresh();
}

// Display the top/bottom border on the puzzle.
void display_border(const int row, const settings& set)
{
  int col = set.term_size.second / 2 - (BOARD_WIDTH * 3 + 1);
  
  for (int i = 1; i <= BOARD_WIDTH; i++)
  {
    set_colour(set.border_connector_colour);
    mvprintw(row, col, set.border_connector.c_str());
    disable_colour(set.border_connector_colour);
    col++;

    set_colour(set.border_edge_span_colour);
    mvprintw(row, col, set.border_edge_span.c_str());
    disable_colour(set.border_edge_span_colour);
    col += 2;
    
    if (i == BOARD_WIDTH)
    {
      set_colour(set.border_connector_colour);
      mvprintw(row, col, set.border_connector.c_str());
      disable_colour(set.border_connector_colour);
    }
  }
}

// Show the Quinze header
void display_header(const settings& set)
{
  center(set.header, 0, set.header_colour);
}

// Display the current state of the puzzle
void display_puzzle(const settings& set, const state& st)
{
  int top_row = set.term_size.first / 2 - BOARD_HEIGHT / 2;
  display_border(top_row, set);
}

// Display the info footer.
void display_footer(const settings& set)
{
  center(set.footer, set.term_size.first-1, set.footer_colour);
}

// Center the text at the given row.
void center(const std::string& text, const int row, const int colour)
{
  int x = get_center_x(text);

  set_colour(colour);
  mvprintw(row, x, text.c_str());
  disable_colour(colour);
}

// Get the x-value needed to center the given text on the screen.
int get_center_x(const std::string& text)
{
  auto size = get_term_size();
  int x = (size.second / 2) - (text.size() / 2);

  return x;
}

// Figure out the current terminal size.
std::pair<int, int> get_term_size()
{
  std::pair<int, int> size = std::make_pair(0, 0);
  getmaxyx(stdscr, size.first, size.second);
  
  return size;
}

// Set or disable the desired colour on the given window.
void set_colour(const int selected_colour)
{
  if ((selected_colour % CURSES_NUM_TOTAL_COLOURS) > COLOUR_WHITE)
  {
    int actual_colour = selected_colour - COLOUR_BOLD_BLACK;
    wattron(stdscr, COLOR_PAIR(actual_colour + 1));
    wattron(stdscr, A_BOLD);

    return;
  }

  wattron(stdscr, COLOR_PAIR(selected_colour + 1));
}

void disable_colour(const int selected_colour)
{
  if ((selected_colour % CURSES_NUM_TOTAL_COLOURS) > COLOUR_WHITE)
  {
    int actual_colour = selected_colour - COLOUR_BOLD_BLACK;
    wattroff(stdscr, COLOR_PAIR(actual_colour+1));
    wattroff(stdscr, A_BOLD);

    return;
  }

  wattroff(stdscr, COLOR_PAIR(selected_colour+1));
}
