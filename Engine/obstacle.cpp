
#include "obstacle.h"

Obstacle::Obstacle() {
}

bool Obstacle::contains(Location const &loc) const {

    for (auto &block : blocks) {

        if (block.getLocation() == loc) {
            return true;
        }
    }

    return false;
}

void Obstacle::grow(Location const &loc) {

    blocks.emplace_back(loc, Colors::Gray);
}

void Obstacle::draw(Board &board) {

    for (auto &block : blocks) {
        block.draw(board);
    }
}

Obstacle::Block::Block(Location const &loc, Color c) : loc(loc), c(c) {
}

Location const &Obstacle::Block::getLocation() const {

    return loc;
}

void Obstacle::Block::draw(Board &board) {

    board.drawCell(loc, c);
}
