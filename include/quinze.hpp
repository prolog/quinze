#pragma once
#include "settings.hpp"
#include "state.hpp"

void print_build_details(const settings& set);
void slide_tiles(state& st);
bool is_movement(const int input);
void check_winner(state& st);
void process_movement_input(state& st, const int input);
void process_input(const settings& set, state& st, bool& keep_playing);
void farewell(const settings& set, const state& st);
void quinze_loop(settings& set, state& st);
void quinze();

