
#include "board.h"

#include <cassert>

Board::Board(Graphics &gfx) : gfx(gfx) {

    int reserve = 2 * dimension;

    width = (Graphics::ScreenWidth - reserve) / dimension;
    height = (Graphics::ScreenHeight - reserve) / dimension;

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

    gfx.DrawRectDim(adjust.x + loc.x * dimension + cell_padding,
                    adjust.y + loc.y * dimension + cell_padding,
                    dimension - 2 * cell_padding, dimension - 2 * cell_padding,
                    c);
}

void Board::drawBorder() {

    Color c(64, 64, 64);

    // top
    gfx.DrawRectDim(0, 0, Graphics::ScreenWidth, adjust.y - cell_padding, c);

    // bottom
    gfx.DrawRectDim(0, 0, adjust.x - cell_padding, Graphics::ScreenHeight, c);

    // left
    gfx.DrawRectDim(0, Graphics::ScreenHeight - gutter.y + cell_padding,
                    Graphics::ScreenWidth, gutter.y - cell_padding, c);

    // right
    gfx.DrawRectDim(Graphics::ScreenWidth - gutter.x + cell_padding, 0,
                    gutter.x - cell_padding, Graphics::ScreenHeight, c);
}
