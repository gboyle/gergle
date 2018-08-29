
#include "board.h"

#include <cassert>

Board::Board(Graphics &gfx) : gfx(gfx) {

    width = (Graphics::ScreenWidth / dimension) - 1;
    height = (Graphics::ScreenHeight / dimension) - 1;

    adjust.x = (Graphics::ScreenWidth - width * dimension) / 2;
    adjust.y = (Graphics::ScreenHeight - height * dimension) / 2;

    gutter.x = Graphics::ScreenWidth - width * dimension - adjust.x;
    gutter.y = Graphics::ScreenHeight - height * dimension - adjust.y;
}

int Board::gridWidth() const {

    return width;
}

int Board::gridHeight() const {

    return height;
}

bool Board::contains(Location const &loc) const {

    return loc.x >= 0 && loc.x < width && loc.y >= 0 && loc.y < height;
}

void Board::drawCell(Location const &loc, Color c) {

    assert(0 <= loc.x);
    assert(loc.x < width);
    assert(0 <= loc.y);
    assert(loc.y < height);

    gfx.DrawRectDim(adjust.x + loc.x * dimension + 1,
                    adjust.y + loc.y * dimension + 1, dimension - 2,
                    dimension - 2, c);
}

void Board::drawBorder() {

    Color c(64, 64, 64);

    gfx.DrawRectDim(0, 0, Graphics::ScreenWidth, adjust.y - 1, c);

    gfx.DrawRectDim(0, 0, adjust.x - 1, Graphics::ScreenHeight, c);

    gfx.DrawRectDim(0, Graphics::ScreenHeight - gutter.y + 1,
                    Graphics::ScreenWidth, gutter.y - 1, c);

    gfx.DrawRectDim(Graphics::ScreenWidth - gutter.x + 1, 0, gutter.x - 1,
                    Graphics::ScreenHeight, c);
}
