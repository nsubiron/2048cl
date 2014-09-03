// 2048cl Copyright (C) 2014 N. Subiron
//
// This program comes with ABSOLUTELY NO WARRANTY. This is free software, and
// you are welcome to redistribute it and/or modify it under the terms of the
// GNU General Public License as published by the Free Software Foundation,
// either version 3 of the License, or (at your option) any later version.

#ifndef DMCO_GRID_H_INCLUDED
#define DMCO_GRID_H_INCLUDED

#include "Defs.h"

namespace dmco {

  class Grid {
    public:

      typedef size_t Tile;

      Grid() : _array{{0u}} {}

      Tile get(Index index) const {
        return _array[index.x][index.y];
      }

      void set(Index index, Tile value) {
        _array[index.x][index.y] = value;
      }

    private:

      Tile _array[GRID_SIZE][GRID_SIZE];
  };

} // namespace dmco

#endif // DMCO_GRID_H_INCLUDED
