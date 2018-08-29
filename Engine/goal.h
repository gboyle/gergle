#pragma once

#include "board.h"
#include "location.h"

#include "Colors.h"

class Goal {

    Location loc = {0, 0};
    Color c = Colors::Red;

  public:
    Goal();

    bool contains(Location const &a_loc);
    void respawn(Location const &new_loc);

    void draw(Board &board) const;
};
