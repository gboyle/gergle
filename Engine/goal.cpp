
#include "goal.h"

Goal::Goal(std::mt19937 &rng, Board const &board, Snake const &snake) {

    respawn(rng, board, snake);
}

void Goal::respawn(std::mt19937 &rng, Board const &board, Snake const &snake) {

    std::uniform_int_distribution<> dist_x(0, board.gridWidth() - 1);
    std::uniform_int_distribution<> dist_y(0, board.gridHeight() - 1);

    Location new_loc;

    do {

        new_loc.x = dist_x(rng);
        new_loc.y = dist_y(rng);

    } while (snake.isInTile(new_loc));

    loc = new_loc;
}

void Goal::draw(Board &board) const {

    board.drawCell(loc, c);
}

Location const &Goal::getLocation() const {

    return loc;
}
