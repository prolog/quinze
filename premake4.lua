#!lua
-- To use, run "premake4 gmake", and then "make config=release".
solution "quize"
  configurations { "Debug", "Release" }

project "quinze"
  kind "ConsoleApp"
  language "C++"
  files { "**.hpp", "**.cpp" }

  includedirs { "include" }
  links { "ncurses" }
  flags { "ExtraWarnings" }

  configuration "Debug"
    defines { "_DEBUG", "DEBUG" }
    flags { "Symbols" }

  configuration "Release"
    defines { "NDEBUG" }
    flags { "Optimize" }


