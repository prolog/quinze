#include "settings.hpp"
#include "display.hpp"

// Create and initialize a new settings object.
settings get_settings()
{
  settings s;
  refresh_settings(s);
  
  return s;
}

// Refresh any settings that may have changed. In practice, this really
// only rechecks the terminal size.
void refresh_settings(settings& set)
{
  set.term_size = get_term_size();
}
