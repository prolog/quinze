#include "display.hpp"

const int CURSES_NUM_TOTAL_COLOURS = 16;
const int CURSES_NUM_BASE_COLOURS = 8;

// The total board height when displayed on the screen (includes borders,
// etc.
const int DISPLAY_BOARD_HEIGHT = (2 * BOARD_HEIGHT) + 1;
const int DISPLAY_BOARD_WIDTH = (3 * BOARD_WIDTH) + 1;

void display_setup()
{
  initscr();
  start_color();
  init_colours();
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

void init_colours()
{
  std::vector<short int> colours{COLOR_BLACK, COLOR_RED, COLOR_GREEN, COLOR_YELLOW, COLOR_BLUE, COLOR_MAGENTA, COLOR_CYAN, COLOR_WHITE};

  short int pair_counter = 1;
  for (auto bg_colour : colours)
  {
    for (auto fg_colour : colours)
    {
      init_pair(pair_counter, fg_colour, bg_colour);
      pair_counter++;
    }

    pair_counter += CURSES_NUM_BASE_COLOURS;
  }
}

// Display the top/bottom border on the puzzle.
void display_border(const int row, const settings& set)
{
  int col = set.term_size.second / 2 - (BOARD_WIDTH * 3 + 1) / 2;
  
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
  int row = set.term_size.first / 2 - DISPLAY_BOARD_HEIGHT / 2;
  int col_start_pos = set.term_size.second / 2 - DISPLAY_BOARD_WIDTH / 2;
  display_border(row, set);

  const auto& board = st.board;

  for (const auto& row_v : board)
  {
    row++;
    int col = col_start_pos;

    move(row, col);
    
    for (size_t i = 0; i < row_v.size(); i++)
    {
      set_colour(set.border_row_span_colour);
      mvprintw(row, col, set.border_row_span.c_str());
      disable_colour(set.border_row_span_colour);
      
      getyx(stdscr, row, col);
      
      std::string val = std::to_string(row_v.at(i));
      set_colour(set.tile_colour);

      if (val == "-1")
      {
	val = "  ";
      }
      else if (val.size() == 1)
      {
	val += " ";
      }

      mvprintw(row, col, val.c_str());
      disable_colour(set.tile_colour);
      getyx(stdscr, row, col);
      
      if (i == row_v.size() - 1)
      {
	set_colour(set.border_row_span_colour);
	mvprintw(row, col, set.border_row_span.c_str());
	disable_colour(set.border_row_span_colour);
	
	getyx(stdscr, row, col);
      }
    }

    row++;

    display_border(row, set);
  }
  
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
