#pragma once
#include <string>
#include <utility>
#include <ncurses.h>
#include "settings.hpp"
#include "state.hpp"

// Set up or destroy the curses display.
void display_setup();
void display_teardown();
void clear_display();
void refresh_display();

// Show the parts of the game screen
void display_border(const int row, const settings& set);
void display_header(const settings& set);
void display_puzzle(const settings& set, const state& st);
void display_footer(const settings& set);

// Text helper functions
void center(const std::string& text, const int row, const int colour);
int get_center_x(const std::string& text);
std::pair<int, int> get_term_size();

// Colour functions
void set_colour(const int colour);
void disable_colour(const int colour);
