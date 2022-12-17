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
  const std::string version = "0.1";
  const std::string author = "Julian Day <jcd748@mail.usask.ca>";
  const int copyright_year = 2022;

  // Game header
  const std::string header = "Q u i n z E";
  const int header_colour = COLOUR_BOLD_WHITE;
  
  // Game footer
  const std::string footer = "q quits, arrows/wasd/vi moves, all others switch";
  const int footer_colour = COLOUR_BOLD_WHITE;
};

settings get_settings();
