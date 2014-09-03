// 2048cl Copyright (C) 2014 N. Subiron
//
// This program comes with ABSOLUTELY NO WARRANTY. This is free software, and
// you are welcome to redistribute it and/or modify it under the terms of the
// GNU General Public License as published by the Free Software Foundation,
// either version 3 of the License, or (at your option) any later version.

#include "Console.h"
#include "Game.h"

#include <exception>
#include <iomanip>
#include <iostream>
#include <limits>
#include <sstream>

using namespace dmco;

template <class OSTREAM>
static OSTREAM &operator<<(OSTREAM &out, const Game &game) {
  out << L"Number of Moves: " << game.getNumberOfMoves() << std::endl;
  out << L"Score:           " << game.getScore() << std::endl;
  out << std::wstring(5u * GRID_SIZE, '-') << std::endl;
  for (int j = GRID_SIZE - 1; j >= 0; --j) {
    for (int i = 0; i < GRID_SIZE; ++i) {
      out << std::setw(5) << game.getTile(Index(i, j));
    }
    out << std::endl;
  }
  return out;
}

static void printGame(const Game &game, const Game::Result &result) {
  std::wostringstream out;
  out << L"Welcome to 2048!" << std::endl << std::endl << game << std::endl;
  if (result == Game::Win)
    out << L"YOU WIN!" << std::endl;
  else if (result == Game::GameOver)
    out << L"GAME OVER" << std::endl;
  else
    out << L"Use arrow keys to move board," << std::endl;
  out << L"press 'q' to exit." << std::endl;
  Console::updateScreen(out.str());
}

int main() {
  try {
    Console::init();

    Game game;
    printGame(game, Game::NothingChanged);

    bool gameFinished = false;

    for (;;) {

      Movement move(Movement::NUMBER_OF_MOVEMENTS);
      switch (Console::getUserAction()) {
        case Console::UserAction::MoveLeft:  move = Movement::Left;  break;
        case Console::UserAction::MoveDown:  move = Movement::Down;  break;
        case Console::UserAction::MoveUp:    move = Movement::Up;    break;
        case Console::UserAction::MoveRight: move = Movement::Right; break;
        case Console::UserAction::Exit:      return 0;
        default:
          break;
      }

      if (gameFinished || (move == Movement::NUMBER_OF_MOVEMENTS))
        continue;

      auto result = game.move(move);
      printGame(game, result);

      if ((result == Game::Win) || (result == Game::GameOver))
        gameFinished = true;
    }

    return 0;
  } catch (const std::exception &e) {
    std::cout << "STL exception thrown" << std::endl << e.what() << std::endl;
    return 1;
  } catch (...) {
    std::cout << "Unknown exception thrown" << std::endl;
    return 2;
  }
}
