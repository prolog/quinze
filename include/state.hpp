#pragma once
#include <string>
#include <vector>
#include <utility>

const int BOARD_WIDTH = 4;
const int BOARD_HEIGHT = 4;

using game_board = std::vector<std::vector<int>>;
using coord = std::pair<int, int>;

// A shift list contains a list of positions and values to assign to
// them - after applying the shift list to the board, the tiles should
// appear to shift.
using shift_list = std::vector<std::pair<coord, int>>;

struct state
{
  int turn = 0;
  coord curs;
  game_board board = {{-1, 1, 2, 3}, {4, 5, 6, 7}, {8, 9, 10, 11}, {12, 13, 14, 15}};
};

state create_new_game();
bool is_winner(const game_board& board);
game_board assign(const std::vector<int>& vals);
void board_err(const game_board& board);
std::string board_str(const game_board& board);
coord find_initial_curs(const game_board& board);
std::vector<int> get_curs_inputs();
coord get_next_curs(const coord& curs, const int key);
std::vector<coord> get_all_adjacent(const game_board& board, const coord& curs);
bool empty_val(const int val);
bool illegal_position(const coord& pos);
shift_list get_shift_list(const game_board& board, const coord& pos);


