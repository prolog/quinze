# quinze
Quinze is a simple, curses-based 15 puzzle.

# Motivation
I wanted to write a complete game, quickly, and have always loved 15-puzzles, ever since discovering the easter egg in Final Fantasy when I was a kid. quinze was written in a Linux VM with emacs and an open terminal.

# Getting Started

## Dependencies
quinze's only dependencies are ncurses (which most Linux distros will have) and premake (which you may need to install). premake is used to generate the makefiles used to build the game.

## Building

```
$ premake4 gmake
$ make config=release
```

# Configuration

Most settings (text, colours, and so on) are located in include/settings.hpp. After editing you will need to re-run make.

## Running

```
$ ./quinze
```

# Playing the Game

Move the cursor with the arrow keys, or wasd. Most other keys will switch, if you can push into an empty square. 'q' quits.

# Planned Features, Roadmap

None. I will happily fix reported bugs, but this project was an attempt to have fun making a complete game, quickly, without needing a big IDE like Visual Studio or CLion. I'm delighted to say I've succeeded.

