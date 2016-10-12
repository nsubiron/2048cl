// 2048cl Copyright (C) 2014 N. Subiron
//
// This program comes with ABSOLUTELY NO WARRANTY. This is free software, and
// you are welcome to redistribute it and/or modify it under the terms of the
// GNU General Public License as published by the Free Software Foundation,
// either version 3 of the License, or (at your option) any later version.

#ifndef DMCO_DEFS_H_INCLUDED
#define DMCO_DEFS_H_INCLUDED

#include <cstdint>

#ifdef _DEBUG
#  include <cassert>
#endif // _DEBUG

#ifdef _DEBUG
#  define DEBUG_CODE(debug_code) debug_code
#else
#  define DEBUG_CODE(debug_code)
#endif // _DEBUG

#define DEBUG_ERROR DEBUG_CODE(assert(false))

#define DEBUG_ASSERT(predicate) DEBUG_CODE(assert(predicate))

namespace dmco {

  using std::size_t;

  constexpr size_t GRID_SIZE = 4u;

  constexpr size_t NUMBER_OF_TILES_TO_ADD = 2u;

  constexpr size_t MAXIMUM_TILE_SCORE = 2048u;

  struct Index {
    constexpr Index(int x, int y) : x(x), y(y) {}
    int x;
    int y;
  };

  enum class Movement : std::int_fast8_t {
    Left,
    Right,
    Up,
    Down,
    NUMBER_OF_MOVEMENTS
  };

} // namespace dmco

#endif // DMCO_DEFS_H_INCLUDED
