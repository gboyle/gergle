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

        void initHead(Location const &in_loc);
        void initTail();

        void moveBy(Location const &delta);
        void follow(Segment const &next);

        Location const &getLocation() const;

        void draw(Board &board);
    };

    std::vector<Segment> segments;

    static constexpr int max_segments = 100;
    static constexpr Color head_color = Colors::Yellow;
    static constexpr Color tail_color = Colors::Green;

  public:
    Snake(Location const &loc);

    void moveBy(Location const &delta);
    void grow();

    Location getNextHead(Location const &delta) const;

    bool isInTileExceptEnd(Location const &loc) const;
    bool isInTile(Location const &loc) const;

    void draw(Board &board);
};
