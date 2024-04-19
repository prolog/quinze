#!lua
-- To use, run "premake4 gmake", and then "make config=release".
solution "quize"
  configurations { "Debug", "Release" }

project "quinze"
  kind "ConsoleApp"
  language "C++"
  files { "include/display.hpp", 
          "include/quinze.hpp",
	  "include/settings.hpp",
	  "include/state.hpp",
	  "source/display.cpp",
	  "source/quinze.cpp",
	  "source/settings.cpp",
	  "source/state.cpp" }

  includedirs { "include" }
  links { "ncurses" }
  flags { "ExtraWarnings" }

  configuration "Debug"
    defines { "_DEBUG", "DEBUG" }
    flags { "Symbols" }

  configuration "Release"
    defines { "NDEBUG" }
    flags { "Optimize" }


