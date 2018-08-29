
#include "snake.h"

#include <cassert>

Snake::Snake(Location const &loc) {

    segments.emplace_back(loc, head_color);
}

void Snake::moveBy(Location const &delta) {

    for (size_t i = segments.size() - 1; i > 0; --i) {
        segments[i].follow(segments[i - 1]);
    }

    segments[0].moveBy(delta);
}

void Snake::grow() {

    if (segments.size() >= max_segments) {
        return;
    }

    const Location end = segments.rbegin()->getLocation();

    segments.emplace_back(end, tail_color);
}

Location Snake::getNextHead(Location const &delta) const {

    return segments[0].getLocation() + delta;
}

bool Snake::isInTileExceptEnd(Location const &loc) const {

    for (int i = 0; i < segments.size() - 1; ++i) {
        if (segments[i].getLocation() == loc) {
            return true;
        }
    }

    return false;
}

bool Snake::isInTile(Location const &loc) const {

    for (auto &segment : segments) {
        if (segment.getLocation() == loc) {
            return true;
        }
    }

    return false;
}

void Snake::draw(Board &board) {

    for (auto it = segments.rbegin(); it != segments.rend(); ++it) {
        it->draw(board);
    }
}

Snake::Segment::Segment(Location const &loc, Color c) : loc(loc), c(c) {
}

void Snake::Segment::initHead(Location const &in_loc) {

    loc = in_loc;
    c = Snake::head_color;
}

void Snake::Segment::initTail() {
    c = Snake::tail_color;
}

void Snake::Segment::moveBy(Location const &delta) {

    assert(abs(delta.x) + abs(delta.y) == 1);

    loc += delta;
}

void Snake::Segment::follow(Segment const &next) {
    loc = next.loc;
}

Location const &Snake::Segment::getLocation() const {
    return loc;
}

void Snake::Segment::draw(Board &board) {
    board.drawCell(loc, c);
}
