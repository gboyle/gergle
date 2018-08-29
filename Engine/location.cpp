
#include "location.h"

Location::Location() : x(0), y(0) {

}

Location::Location(int x, int y) : x(x), y(y) {

}

Location &Location::operator+=(Location const &rhs) {

    x += rhs.x;
    y += rhs.y;

    return *this;
}

Location Location::operator+(Location const &rhs) const {

    return Location(x + rhs.x, y + rhs.y);
}

bool Location::operator==(Location const &rhs) const {

    return x == rhs.x && y == rhs.y;
}
