// 2048cl Copyright (C) 2014 N. Subiron
//
// This program comes with ABSOLUTELY NO WARRANTY. This is free software, and
// you are welcome to redistribute it and/or modify it under the terms of the
// GNU General Public License as published by the Free Software Foundation,
// either version 3 of the License, or (at your option) any later version.

#include "Dynamics.h"

#include "Grid.h"

#include <cstdlib>

namespace dmco {

  enum IteratorIncrement {
    Increment,
    Decrement
  };

  enum IteratorDirection {
    X,
    Y
  };

  template <enum IteratorIncrement INCREMENT, enum IteratorDirection DIRECTION>
  class GridIterator {
    public:

      typedef GridIterator<INCREMENT, DIRECTION> Self;

      GridIterator() : _index(0, 0) {
        Self::getFirst(_index) = Self::getStart();
      }

      GridIterator(const Self &rhs) : _index(rhs._index) {}

      bool increment() {
        return ++Self::getFirst(_index) < Self::getEnd();
      }

      bool jump() {
        Self::getFirst(_index) = Self::getStart();
        return ++Self::getSecond(_index) < GRID_SIZE;
      }

      Index operator*() const {
        return Index(std::abs(_index.x), std::abs(_index.y));
      }

      bool operator!=(const Self &rhs) const {
        return (_index.x != rhs._index.x) || (_index.y != rhs._index.y);
      }

    private:

      static constexpr int getEnd() {
        return INCREMENT == Increment ? static_cast<int>(GRID_SIZE) : 1;
      }

      static constexpr int getStart() {
        return INCREMENT == Increment ? 0 : 1 - static_cast<int>(GRID_SIZE);
      }

      static constexpr int &getFirst(Index &index) {
        return DIRECTION == X ? index.x : index.y;
      }

      static constexpr int &getSecond(Index &index) {
        return DIRECTION == X ? index.y : index.x;
      }

      Index _index;
  };

  typedef GridIterator<Increment, X> IteratorLeft;
  typedef GridIterator<Decrement, X> IteratorRight;
  typedef GridIterator<Increment, Y> IteratorDown;
  typedef GridIterator<Decrement, Y> IteratorUp;

  template <class ITERATOR>
  static bool move(Grid &grid, Dynamics::MoveStats &stats) {
    bool anyChange = false;
    ITERATOR iterator;
    do {
      ITERATOR begin(iterator);
      while (iterator.increment()) {
        while (begin != iterator) {
          auto source = grid.get(*iterator);
          if (source == 0u)
            break;
          auto destination = grid.get(*begin);
          if (destination == 0u) {
            // Move source to destination.
            grid.set(*begin, source);
            grid.set(*iterator, 0u);
            anyChange = true;
            break;
          } else if (destination == source) {
            // Merge.
            const size_t mergedValue = 2u * source;
            grid.set(*begin, mergedValue);
            grid.set(*iterator, 0u);
            begin.increment();
            stats.score += mergedValue;
            if (mergedValue > stats.higherMergedValue)
              stats.higherMergedValue = mergedValue;
            anyChange = true;
            break;
          } else {
            begin.increment();
          }
       }
      }
    } while (iterator.jump());
    return anyChange;
  }

  bool Dynamics::areMovesAvailable(const Grid &grid) {
    for (size_t x = 0u; x < GRID_SIZE; ++x) {
      for (size_t y = 0u; y < GRID_SIZE; ++y) {
        const size_t value = grid.get(Index(x, y));
        if (value == 0u)
          return true;
        if ((x != GRID_SIZE - 1) && (value == grid.get(Index(x + 1, y))))
          return true;
        if ((y != GRID_SIZE - 1) && (value == grid.get(Index(x, y + 1))))
          return true;
      }
    }
    return false;
  }

  bool Dynamics::move(Grid &grid, Movement movement, MoveStats &stats) {
    switch (movement) {
      case Movement::Left:  return dmco::move<IteratorLeft>(grid, stats);
      case Movement::Right: return dmco::move<IteratorRight>(grid, stats);
      case Movement::Down:  return dmco::move<IteratorDown>(grid, stats);
      case Movement::Up:    return dmco::move<IteratorUp>(grid, stats);
      default:
        DEBUG_ERROR;
        return false;
    }
  }

} // namespace dmco
