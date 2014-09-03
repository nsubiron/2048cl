// 2048cl Copyright (C) 2014 N. Subiron
//
// This program comes with ABSOLUTELY NO WARRANTY. This is free software, and
// you are welcome to redistribute it and/or modify it under the terms of the
// GNU General Public License as published by the Free Software Foundation,
// either version 3 of the License, or (at your option) any later version.

#include "Console.h"

#include <curses.h>

namespace dmco {

  class ConsoleGuard {
    public:

      ConsoleGuard() {
        initscr();
        keypad(stdscr, TRUE);
        noecho();
        curs_set(0);
      }

      ~ConsoleGuard() {
        endwin();
      }
  };

  void Console::init() {
    static const ConsoleGuard guard;
  }

  Console::UserAction Console::getUserAction() {
    switch (getch())  {
      case KEY_LEFT:  return UserAction::MoveLeft;
      case KEY_RIGHT: return UserAction::MoveRight;
      case KEY_DOWN:  return UserAction::MoveDown;
      case KEY_UP:    return UserAction::MoveUp;
      case 'q':       return UserAction::Exit;
      default:        return UserAction::Undefined;
    }
  }

  void Console::updateScreen(const std::wstring &text) {
    clear();
    for (auto c : text)
      addch(c);
    refresh();
  }

} // namespace dmco

