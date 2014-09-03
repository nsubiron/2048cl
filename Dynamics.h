// 2048cl Copyright (C) 2014 N. Subiron
//
// This program comes with ABSOLUTELY NO WARRANTY. This is free software, and
// you are welcome to redistribute it and/or modify it under the terms of the
// GNU General Public License as published by the Free Software Foundation,
// either version 3 of the License, or (at your option) any later version.

#ifndef DMCO_DYNAMICS_H_INCLUDED
#define DMCO_DYNAMICS_H_INCLUDED

#include "Defs.h"

namespace dmco {

  class Grid;

  class Dynamics {
    public:

      struct MoveStats {
        MoveStats() : higherMergedValue(0u), score(0u) {}
        size_t higherMergedValue;
        size_t score;
      };

      static bool areMovesAvailable(const Grid &grid);

      /// Return whether the grid changed.
      static bool move(Grid &grid, Movement movement, MoveStats &stats);
  };

} // namespace dmco

#endif // DMCO_DYNAMICS_H_INCLUDED
