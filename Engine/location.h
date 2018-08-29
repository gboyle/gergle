#pragma once

struct Location {

    int x;
    int y;

    Location();
    Location(int x, int y);

    Location &operator+=(Location const &rhs);
    Location operator+(Location const &rhs) const;
    bool operator==(Location const &rhs) const;
};
