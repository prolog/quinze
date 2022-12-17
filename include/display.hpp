#pragma once
#include <ncurses.h>

// Set up or destroy the curses display.
void display_setup();
void display_teardown();

// Show the parts of the game screen
void display_header();
void display_puzzle();
void display_footer();
