#pragma once

#include "Graphics.h"
#include "location.h"

class Board {

    static constexpr int dimension = 20;

    Graphics &gfx;

    int width = 10;
    int height = 10;

  public:
    explicit Board(Graphics &gfx);

    int gridWidth() const;
    int gridHeight() const;

    bool isInside(Location const &loc) const;

    void drawCell(Location const &loc, Color c);
};
