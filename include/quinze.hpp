#pragma once
#include "settings.hpp"
#include "state.hpp"

void print_build_details(const settings& set);
int process_input();
void farewell();
void quinze_loop(settings& set, state& st);
void quinze();

