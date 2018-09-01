
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

    cells.resize(width * height, CellContents::Empty);
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

Board::CellContents Board::getContents(Location const &loc) const {

    return cells[loc.y * width + loc.x];
}

void Board::setContents(Location const &loc, CellContents type) {

    cells[loc.y * width + loc.x] = type;
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

void Board::drawObstacles() {

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {

            switch (cells[y * width + x]) {
            case CellContents::Obstacle:
                drawCell({x, y}, obstacle_color);
                break;
            case CellContents::Poison:
                drawCell({x, y}, poison_color);
                break;
            case CellContents::Food:
                drawCell({x, y}, food_color);
                break;
            default:
                // nop
                break;
            }
        }
    }
}
