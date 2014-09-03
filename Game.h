// 2048cl Copyright (C) 2014 N. Subiron
//
// This program comes with ABSOLUTELY NO WARRANTY. This is free software, and
// you are welcome to redistribute it and/or modify it under the terms of the
// GNU General Public License as published by the Free Software Foundation,
// either version 3 of the License, or (at your option) any later version.

#ifndef DMCO_GAME_H_INCLUDED
#define DMCO_GAME_H_INCLUDED

#include "Defs.h"
#include "Grid.h"

#include <memory>

namespace dmco {

  class Game {
    public:

      enum Result {
        Win,
        GameOver,
        NothingChanged,
        KeepTrying
      };

      Game();

      ~Game();

      size_t getTile(Index index) const {
        return _grid.get(index);
      }

      size_t getNumberOfMoves() const {
        return _numberOfMoves;
      }

      size_t getScore() const {
        return _score;
      }

      Result move(Movement move);

    private:

      class Pimpl;
      typedef std::unique_ptr<Pimpl> UpPimpl;

      UpPimpl _pimpl;

      Grid _grid;

      size_t _numberOfMoves;

      size_t _score;
  };

} // namespace dmco

#endif // DMCO_GAME_H_INCLUDED
