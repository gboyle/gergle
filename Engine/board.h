#pragma once

#include "Colors.h"
#include "Graphics.h"

#include "location.h"

#include <vector>

class Board {

    static constexpr int dimension = 20;
    static constexpr int cell_padding = 1;

    Graphics &gfx;

    int width = 10;
    int height = 10;

    Location adjust;
    Location gutter;

    std::vector<char> has_obstacle;

    static constexpr Color obstacle_color = Colors::LightGray;
	static constexpr Color poison_color = { 128, 0, 128 };

  public:
    explicit Board(Graphics &gfx);

    int gridWidth() const;
    int gridHeight() const;

    bool contains(Location const &loc) const;

    char checkForObstacle(Location const &loc) const;
    void setObstacle(Location const &loc, char type);

    void drawCell(Location const &loc, Color c);
    void drawBorder();
    void drawObstacles();
};
