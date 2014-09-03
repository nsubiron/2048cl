// 2048cl Copyright (C) 2014 N. Subiron
//
// This program comes with ABSOLUTELY NO WARRANTY. This is free software, and
// you are welcome to redistribute it and/or modify it under the terms of the
// GNU General Public License as published by the Free Software Foundation,
// either version 3 of the License, or (at your option) any later version.

#ifndef DMCO_CONSOLE_H_INCLUDED
#define DMCO_CONSOLE_H_INCLUDED

#include <string>

namespace dmco {

  /// Console interface around ncurses library. init() must be called before any
  /// other method.
  class Console {
    public:

      enum class UserAction {
        MoveLeft,
        MoveRight,
        MoveUp,
        MoveDown,
        Exit,
        Undefined
      };

      static void init();

      /// Wait for the user to press a key and return the corresponding action
      /// if valid, return UserAction::Undefined otherwise.
      static UserAction getUserAction();

      /// Clear current screen and print @a text.
      static void updateScreen(const std::wstring &text);
  };

} // namespace dmco

#endif // DMCO_CONSOLE_H_INCLUDED
