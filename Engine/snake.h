#pragma once

#include "Colors.h"

#include "board.h"
#include "location.h"

#include <vector>

class Snake {

    class Segment {

        Location loc;
        Color c;

      public:
        Segment(Location const &loc, Color c);

        void moveBy(Location const &delta);
        void follow(Segment const &next);

        Location const &getLocation() const;

        void draw(Board &board);
    };

    std::vector<Segment> segments;

    static constexpr int max_segments = 100;
    static constexpr Color head_color = Colors::Yellow;

  public:
    Snake(Location const &loc);

    void moveBy(Location const &delta);
    void grow();

    Location getNextHead(Location const &delta) const;

    bool contains(Location const &loc, bool growing = false) const;

    void draw(Board &board);
};
