
#include "board.h"

#include <cassert>

Board::Board(Graphics &gfx)
    : gfx(gfx),
      width(Graphics::ScreenWidth / dimension),
      height(Graphics::ScreenHeight / dimension) {}

int Board::gridWidth() { return width; }

int Board::gridHeight() { return height; }

void Board::drawCell(Location const &loc, Color c) {

    assert(0 <= loc.x);
    assert(loc.x < width);
    assert(0 <= loc.y);
    assert(loc.y < height);

    gfx.DrawRectDim(loc.x * dimension, loc.y * dimension, dimension, dimension,
                    c);
}
