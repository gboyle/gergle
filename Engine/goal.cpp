
#include "goal.h"

Goal::Goal() {
}

bool Goal::contains(Location const &a_loc) {

    return loc == a_loc;
}

void Goal::respawn(Location const &new_loc) {

    loc = new_loc;
}

void Goal::draw(Board &board) const {

    board.drawCell(loc, c);
}
