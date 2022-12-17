#pragma once
#include <string>

struct settings
{
  const std::string version = "0.1";
  const std::string author = "Julian Day <jcd748@mail.usask.ca>";
  const int copyright_year = 2022;
};

settings get_settings();
