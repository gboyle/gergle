#pragma once

#include "board.h"
#include "snake.h"

#include <random>

class Goal {

    Location loc;
    Color c = Colors::Red;

  public:
    Goal(std::mt19937 &rng, Board const &board, Snake const &snake);

    void respawn(std::mt19937 &rng, Board const &board, Snake const &snake);
    Location const &getLocation() const;

    void draw(Board &board) const;
};
