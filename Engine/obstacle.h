#pragma once

#include "board.h"
#include "snake.h"

#include <random>

class Obstacle {

    class Block {

        Location loc;
        Color c;

      public:
        Block(Location const &loc, Color c);

        Location const &getLocation() const;

        void draw(Board &board);
    };

    std::vector<Block> blocks;

  public:
    Obstacle();

    bool contains(Location const &loc) const;
    void grow(Location const &loc);

    void draw(Board &board);
};
