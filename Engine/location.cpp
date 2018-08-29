
#include "location.h"

Location::Location(int x, int y) : x(x), y(y) {}

Location &Location::operator+=(Location const &rhs) {

    x += rhs.x;
    y += rhs.y;

    return *this;
}
