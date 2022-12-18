#include <random>
#include <algorithm>
#include "state.hpp"
#include <iostream>
#include <sstream>

// Create a new game state, shuffling it until it's not in a winner state.
state create_new_game()
{
  state s;
  std::random_device rd;
  std::mt19937 g(rd());
  std::vector<int> vals = {-1, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
  std::shuffle(vals.begin(), vals.end(), g);
  
  std::vector<std::vector<int>> new_board(4, std::vector<int>(4));
  new_board = assign(vals);
  
  while (is_winner(new_board))
  {
    std::shuffle(vals.begin(), vals.end(), g);
    new_board = assign(vals);
  }

  s.board = new_board;

  return s;
}

// Check to see if the board is a winner. It needs to be height * width
// (16) and needs to have values in ascending order, ignoring -1, which
// is used to represent the empty square.
bool is_winner(const std::vector<std::vector<int>>& board)
{
  int cnt = 0;
  int lowest = -2;
  
  for (int i = 0; i < BOARD_HEIGHT; i++)
  {
    for (int j = 0; j < BOARD_HEIGHT; j++)
    {
      int val = board[i][j];
      cnt++;

      if (val == -1)
      {
	continue;
      }
      else
      {
	if (val < lowest)
	{
	  return false;
	}
	else
	{
	  lowest = val;
	}
      }
    }
  }
  std::cerr << cnt << std::endl;  
  return (cnt == BOARD_HEIGHT * BOARD_WIDTH);
}

// Create a 4x4 board using a flat vector of values.
std::vector<std::vector<int>> assign(const std::vector<int>& vals)
{
  std::vector<std::vector<int>> board(4, std::vector<int>(4));

  if (vals.size() == BOARD_HEIGHT * BOARD_WIDTH)
  {
    for (int i = 0; i < BOARD_HEIGHT; i++)
    {
      for (int j = 0; j < BOARD_WIDTH; j++)
      {
	board[i][j] = vals[BOARD_WIDTH * i + j];
      }
    }
  }

  return board;
}

// Dump the board
void board_err(const std::vector<std::vector<int>>& board)
{
  std::cerr << board_str(board) << std::endl;
}

// Create a string representation of the board that can be eg dumped to
// stderr.
std::string board_str(const std::vector<std::vector<int>>& board)
{
  std::ostringstream ss;

  for (const auto& row : board)
  {
    for (const auto& col_val : row)
    {
      ss << col_val << " ";
    }
  }

  return ss.str();
}
