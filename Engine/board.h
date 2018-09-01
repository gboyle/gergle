#pragma once

#include "Colors.h"
#include "Graphics.h"

#include "location.h"

#include <vector>

class Board {

  public:
    enum class CellContents: unsigned char { Empty = 0, Obstacle, Food, Poison };

  private:
    static constexpr int dimension = 20;
    static constexpr int cell_padding = 1;

    Graphics &gfx;

    int width = 10;
    int height = 10;

    Location adjust;
    Location gutter;

    std::vector<CellContents> cells;

    static constexpr Color obstacle_color = Colors::LightGray;
    static constexpr Color poison_color = {64, 0, 64};
    static constexpr Color food_color = Colors::Red;

  public:
    explicit Board(Graphics &gfx);

    int gridWidth() const;
    int gridHeight() const;

    bool contains(Location const &loc) const;

    CellContents getContents(Location const &loc) const;
    void setContents(Location const &loc, CellContents contents);

    void drawCell(Location const &loc, Color c);
    void drawBorder();
    void drawObstacles();
};
