#pragma once
#include <string>
#include <vector>
#include <utility>

const int BOARD_WIDTH = 4;
const int BOARD_HEIGHT = 4;

struct state
{
  int turn = 0;
  std::pair<int, int> curs;
  std::vector<std::vector<int>> board = {{-1, 1, 2, 3}, {4, 5, 6, 7}, {8, 9, 10, 11}, {12, 13, 14, 15}};
};

state create_new_game();
bool is_winner(const std::vector<std::vector<int>>& board);
std::vector<std::vector<int>> assign(const std::vector<int>& vals);
void board_err(const std::vector<std::vector<int>>& board);
std::string board_str(const std::vector<std::vector<int>>& board);
std::pair<int, int> find_initial_curs(const std::vector<std::vector<int>>& board);
std::vector<int> get_curs_inputs();
std::pair<int, int> get_next_curs(const std::pair<int, int>& curs, const int key);
std::vector<std::pair<int, int>> get_all_adjacent(const std::vector<std::vector<int>>& board, const std::pair<int, int>& curs);
bool empty_val(const int val);
bool empty(const std::vector<std::vector<int>>& board, const std::pair<int, int>& coord);
std::pair<int, int> get_empty_adjacent(const std::vector<std::vector<int>>& board, const std::pair<int, int>& pos);

