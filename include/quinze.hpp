#pragma once
#include "settings.hpp"
#include "state.hpp"

void print_build_details(const settings& set);
bool is_movement(const int input);
void process_movement_input(state& st, const int input);
void process_input(state& st, bool& keep_playing);
void farewell();
void quinze_loop(settings& set, state& st);
void quinze();

