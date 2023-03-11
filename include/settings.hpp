#pragma once
#include <string>

constexpr int COLOUR_BLACK = 0;
constexpr int COLOUR_RED = 1;
constexpr int COLOUR_GREEN = 2;
constexpr int COLOUR_YELLOW = 3;
constexpr int COLOUR_BLUE = 4;
constexpr int COLOUR_MAGENTA = 5;
constexpr int COLOUR_CYAN = 6;
constexpr int COLOUR_WHITE = 7;
constexpr int COLOUR_BOLD_BLACK = 8;
constexpr int COLOUR_BOLD_RED = 9;
constexpr int COLOUR_BOLD_GREEN = 10;
constexpr int COLOUR_BOLD_YELLOW = 11;
constexpr int COLOUR_BOLD_BLUE = 12;
constexpr int COLOUR_BOLD_MAGENTA = 13;
constexpr int COLOUR_BOLD_CYAN = 14;
constexpr int COLOUR_BOLD_WHITE = 15;

struct settings
{
  // Misc
  const std::string version = "0.12";
  const std::string author = "Julian Day <jcd748@mail.usask.ca>";
  const int copyright_year = 2023;
  std::pair<int, int> term_size = std::make_pair(0, 0);
  const std::string quit_prompt = "Really quit? (y/n)";
  const int quit_prompt_colour = COLOUR_BOLD_WHITE;
  std::string farewell = "Thanks for playing!";
  std::string farewell_winner = "Thanks for winning!";
  
  // Game header
  const std::string header = "Q u i n z E";
  const std::string header_winner = "Q u i n z E - Winner!";
  const int header_colour = COLOUR_BOLD_WHITE;

  // Border details
  const std::string border_connector = "+";
  const std::string border_edge_span = "--";
  const std::string border_row_span = "|";
  const int border_connector_colour = COLOUR_BOLD_CYAN;
  const int border_edge_span_colour = COLOUR_CYAN;
  const int border_row_span_colour = COLOUR_CYAN;

  // Tile details
  const int tile_colour = COLOUR_BOLD_GREEN;
  
  // Game footer
  const std::string footer = "q quits, arrows/wasd move, and all others switch";
  const std::string footer_winner = "q quits!";  
  const int footer_colour = COLOUR_BOLD_WHITE;
};

settings get_settings();
void refresh_settings(settings& set);
