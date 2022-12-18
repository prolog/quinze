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
