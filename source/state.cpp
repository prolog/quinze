#include <random>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <ncurses.h>
#include "state.hpp"

const int EMPTY_BOARD_VAL = -1;

// Create a new game state, shuffling it until it's not in a winner state.
state create_new_game()
{
  state s;
  std::random_device rd;
  std::mt19937 g(rd());

  // To easily test the victory condition, comment out the std::shuffle
  // below.
  std::vector<int> vals = {1, 2, 3, 4, 5, 6, 7, 8, 9, 13, 10, 11, 12, -1, 14, 15};
  //std::shuffle(vals.begin(), vals.end(), g);
  s.curs = std::make_pair(0, 0);
  
  game_board new_board(4, std::vector<int>(4));
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
bool is_winner(const game_board& board)
{
  int cnt = 0;
  int lowest = -2;
  
  for (int i = 0; i < BOARD_HEIGHT; i++)
  {
    for (int j = 0; j < BOARD_HEIGHT; j++)
    {
      int val = board[i][j];
      cnt++;

      if (empty_val(val))
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
game_board assign(const std::vector<int>& vals)
{
  game_board board(4, std::vector<int>(4));

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
void board_err(const game_board& board)
{
  std::cerr << board_str(board) << std::endl;
}

// Create a string representation of the board that can be eg dumped to
// stderr.
std::string board_str(const game_board& board)
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
coord find_initial_curs(const game_board& board)
{
  coord curs = std::make_pair(0, 0);

  for (size_t i = 0; i < board.size(); i++)
  {
    std::vector<int> row = board.at(i);
    
    for (size_t j = 0; j < row.size(); j++)
    {
      int val = row.at(j);

      if (empty_val(val))
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

coord get_next_curs(const coord& curs, const int key)
{
  coord next_curs = curs;

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

std::vector<coord> get_all_adjacent(const game_board&, const coord& curs)
{
  std::vector<coord> adj;

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
  return val == EMPTY_BOARD_VAL;
}

bool illegal_position(const coord& pos)
{
  return (pos.first < 0 || pos.first >= BOARD_HEIGHT || pos.second < 0 || pos.second >= BOARD_WIDTH);
}

shift_list get_shift_list(const game_board& board, const coord& pos)
{
  std::vector<std::pair<int, int>> offsets = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

  // Can't shift on the empty tile.
  int val = board[pos.first][pos.second];

  if (empty_val(val))
  {
    return {};
  }
  
  for (const auto& off_pair : offsets)
  {
    shift_list shifts;
    coord prev = pos;

    while (true)
    {
      coord cur = prev;
      
      cur.first += off_pair.first;
      cur.second += off_pair.second;      

      if (illegal_position(cur))
      {
	break;
      }
      else
      {
	int shift_val = board[prev.first][prev.second];
	shifts.push_back(std::make_pair(cur, shift_val));

	int cur_val = board[cur.first][cur.second];

	if (empty_val(cur_val))
	{
	  shifts.push_back(std::make_pair(pos, EMPTY_BOARD_VAL));
	  return shifts;
	}
      }

      prev = cur;
    }
  }

  return {};
}

