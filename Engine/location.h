#pragma once

struct Location {

    int x;
    int y;

    Location(int x, int y);
    Location &operator+=(Location const &rhs);
};
