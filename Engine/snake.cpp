
#include "snake.h"

#include <cassert>

Snake::Snake(Location const &loc) { segments.emplace_back(loc, head_color); }

void Snake::moveBy(Location const &delta) {

    for (size_t i = segments.size() - 1; i > 0; --i) {
        segments[i].follow(segments[i - 1]);
    }

    segments[0].moveBy(delta);
}

void Snake::grow() {

    if (segments.size() >= max_segments) { return; }

    segments.emplace_back(Location(0, 0), tail_color);
}

void Snake::draw(Board &board) {

    for (auto &segment : segments) {
        segment.draw(board);
    }
}

Snake::Segment::Segment(Location const &loc, Color c) : loc(loc), c(c) {}

void Snake::Segment::initHead(Location const &in_loc) {

    loc = in_loc;
    c = Snake::head_color;
}

void Snake::Segment::initTail() { c = Snake::tail_color; }

void Snake::Segment::moveBy(Location const &delta) {

    assert(abs(delta.x) + abs(delta.y) == 1);

    loc += delta;
}

void Snake::Segment::follow(Segment const &next) { loc = next.loc; }

void Snake::Segment::draw(Board &board) { board.drawCell(loc, c); }
