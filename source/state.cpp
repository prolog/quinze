#include <random>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <ncurses.h>
#include "state.hpp"

// Create a new game state, shuffling it until it's not in a winner state.
state create_new_game()
{
  state s;
  std::random_device rd;
  std::mt19937 g(rd());
  std::vector<int> vals = {-1, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
  std::shuffle(vals.begin(), vals.end(), g);
  s.curs = std::make_pair(0, 0);
  
  std::vector<std::vector<int>> new_board(4, std::vector<int>(4));
  new_board = assign(vals);
  
  while (is_winner(new_board))
  {
    std::shuffle(vals.begin(), vals.end(), g);
    new_board = assign(vals);
  }

  s.board = new_board;
  s.curs = find_initial_curs(s.board);
  
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

// Figure out where the initial cursor should go.
std::pair<int, int> find_initial_curs(const std::vector<std::vector<int>>& board)
{
  std::pair<int, int> curs = std::make_pair(0, 0);

  for (size_t i = 0; i < board.size(); i++)
  {
    std::vector<int> row = board.at(i);
    
    for (size_t j = 0; j < row.size(); j++)
    {
      int val = row.at(j);

      if (val == -1)
      {
	if (j == 0)
	{
	  return std::make_pair(i, j+1);
	}
	else
	{
	  return std::make_pair(i, j-1);
	}
      }
    }	   
  }
  
  return curs;
}

std::vector<int> get_curs_inputs()
{
  return  {'w', 'W', 'a', 'A', 's', 'S', 'd', 'D', KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT};
}

std::pair<int, int> get_next_curs(const std::pair<int, int>& curs, const int key)
{
  std::pair<int, int> next_curs = curs;

  if (key == 'w' || key == 'W' || key == KEY_UP)
  {
    next_curs.first--;
  }
  else if (key == 'a' || key == 'A' || key == KEY_LEFT)
  {
    next_curs.second--;
  }
  else if (key == 's' || key == 'S' || key == KEY_DOWN)
  {
    next_curs.first++;
  }
  else if (key == 'd' || key == 'D' || key == KEY_RIGHT)
  {
    next_curs.second++;
  }

  // If we've moved beyond the bounds of the board, just return the
  // current cursor.
  if (next_curs.first < 0 || next_curs.second < 0 || next_curs.first >= BOARD_HEIGHT || next_curs.second >= BOARD_WIDTH)
  {
    return curs;
  }
  // Otherwise return the new cursor.
  else
  {
    return next_curs;
  }
}

std::vector<std::pair<int, int>> get_all_adjacent(const std::vector<std::vector<int>>&, const std::pair<int, int>& curs)
{
  std::vector<std::pair<int, int>> adj;

  // N
  if (curs.first > 0)
  {
    adj.push_back({curs.first-1, curs.second});
  }

  // S
  if (curs.first < BOARD_HEIGHT - 1)
  {
    adj.push_back({curs.first+1, curs.second});
  }

  // E
  if (curs.second < BOARD_WIDTH - 1)
  {
    adj.push_back({curs.first, curs.second+1});
  }

  // W
  if (curs.second > 0)
  {
    adj.push_back({curs.first, curs.second-1});
  }

  return adj;
}

bool empty_val(const int val)
{
  return val == -1;
}

bool empty(const std::vector<std::vector<int>>& board, const std::pair<int, int>& coord)
{
  bool e = false;

  try
  {
    std::vector<int> row = board.at(coord.first);
    int val = row.at(coord.second);

    return empty_val(val);
  }
  catch(...)
  {
  }

  return e;
}

std::pair<int, int> get_empty_adjacent(const std::vector<std::vector<int>>& board, const std::pair<int, int>& pos)
{
  std::pair<int, int> adj = {-1, -1};
  auto adj_maybe = get_all_adjacent(board, pos);

  for (const auto& maybe : adj_maybe)
  {
    if (empty(board, maybe))
    {
      return maybe;
    }
  }
  
  return adj;
}

