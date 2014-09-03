// 2048cl Copyright (C) 2014 N. Subiron
//
// This program comes with ABSOLUTELY NO WARRANTY. This is free software, and
// you are welcome to redistribute it and/or modify it under the terms of the
// GNU General Public License as published by the Free Software Foundation,
// either version 3 of the License, or (at your option) any later version.

#include "Game.h"

#include "Dynamics.h"
#include "Grid.h"

#include <algorithm>
#include <random>
#include <vector>

namespace dmco {

  // ===========================================================================
  // -- Game::Pimpl ------------------------------------------------------------
  // ===========================================================================

  class Game::Pimpl {
    public:

      Pimpl() :
        _randomEngine(std::random_device()()) {
        _randomIndices.reserve(GRID_SIZE * GRID_SIZE);
        for (size_t i = 0u; i < GRID_SIZE; ++i)
          for (size_t j = 0u; j < GRID_SIZE; ++j)
            _randomIndices.emplace_back(i, j);
      }

      size_t getRandomTile() {
        return _uniformDistribution(_randomEngine) < 0.9 ? 2u : 4u;
      }

      void addRandomTiles(Grid &grid, const size_t count);

    private:

      std::mt19937 _randomEngine;

      std::uniform_real_distribution<> _uniformDistribution;

      std::vector<Index> _randomIndices;
  };

  void Game::Pimpl::addRandomTiles(Grid &grid, const size_t count) {
    std::shuffle(_randomIndices.begin(), _randomIndices.end(), _randomEngine);
    size_t counter = 0u;
    for (auto index : _randomIndices) {
      if (0u == grid.get(index)) {
        grid.set(index, getRandomTile());
        if (++counter == count)
          break;
      }
    }
  }

  // ===========================================================================
  // -- Game -------------------------------------------------------------------
  // ===========================================================================

  Game::Game() : _pimpl(new Pimpl), _grid(), _numberOfMoves(0u), _score(0u) {
    _pimpl->addRandomTiles(_grid, NUMBER_OF_TILES_TO_ADD);
  }

  Game::~Game() {}

  Game::Result Game::move(Movement move) {
    Dynamics::MoveStats stats;
    if (! Dynamics::move(_grid, move, stats))
      return NothingChanged;

    ++_numberOfMoves;

    _score += stats.score;

    if (stats.higherMergedValue >= MAXIMUM_TILE_SCORE)
      return Win;

    _pimpl->addRandomTiles(_grid, NUMBER_OF_TILES_TO_ADD);

    if (Dynamics::areMovesAvailable(_grid))
      return KeepTrying;

    return GameOver;
  }

} //namespace dmco
