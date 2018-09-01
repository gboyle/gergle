/******************************************************************************************
*	Chili DirectX Framework Version 16.07.20											  *
*	Graphics.cpp																		  *
*	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
*																						  *
*	This file is part of The Chili DirectX Framework.									  *
*																						  *
*	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
*	it under the terms of the GNU General Public License as published by				  *
*	the Free Software Foundation, either version 3 of the License, or					  *
*	(at your option) any later version.													  *
*																						  *
*	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
*	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
*	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
*	GNU General Public License for more details.										  *
*																						  *
*	You should have received a copy of the GNU General Public License					  *
*	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
******************************************************************************************/

#include "Game.h"
#include "MainWindow.h"
#include "SpriteCodex.h"

Game::Game(MainWindow &wnd)
    : wnd(wnd),
      gfx(wnd),
      rng(std::random_device()()),
      board(gfx),
      snake({2, 2}) {

    int poison_count = board.gridWidth() * board.gridWidth() / 10;
    for (int i = 0; i < poison_count; ++i) {
        Location loc = getOpenLocation();
        board.setContents(loc, Board::CellContents::Poison);
    }

    int food_count = board.gridWidth() * board.gridWidth() / 200 + 1;
    for (int i = 0; i < food_count; ++i) {
        Location loc = getOpenLocation();
        board.setContents(loc, Board::CellContents::Food);
    }

    int obstacle_count = board.gridWidth() * board.gridWidth() / 200 + 1;
    for (int i = 0; i < obstacle_count; ++i) {
        Location loc = getOpenLocation();
        board.setContents(loc, Board::CellContents::Obstacle);
    }
}

void Game::Go() {
    gfx.BeginFrame();
    UpdateModel();
    ComposeFrame();
    gfx.EndFrame();
}

void Game::UpdateModel() {

    const float dt = frame_rate.mark();

    if (game_over) {
        return;
    }

    if (!game_started) {

        if (wnd.kbd.KeyIsPressed(VK_RETURN)) {
            game_started = true;
        }

        return;
    }

    if (wnd.kbd.KeyIsPressed(VK_UP)) {
        delta = {0, -1};
    }

    if (wnd.kbd.KeyIsPressed(VK_DOWN)) {
        delta = {0, 1};
    }

    if (wnd.kbd.KeyIsPressed(VK_LEFT)) {
        delta = {-1, 0};
    }

    if (wnd.kbd.KeyIsPressed(VK_RIGHT)) {
        delta = {1, 0};
    }

    snake_move_elapsed += dt;

    if (snake_move_elapsed > snake_move_threshold) {

        snake_move_elapsed -= snake_move_threshold;

        const Location next = snake.getNextHead(delta);

        if (!board.contains(next)) {
            game_over = true;
            return;
        }

        Board::CellContents contents = board.getContents(next);

        bool growing = contents == Board::CellContents::Food;

        if (snake.contains(next, growing)) {
            game_over = true;
            return;
        }

        if (contents == Board::CellContents::Obstacle) {
            game_over = true;
            return;
        }

        if (contents == Board::CellContents::Poison) {
            speedUp();
        }

        if (growing) {
            snake.grow();
        }

        snake.moveBy(delta);

        if (growing) {

			board.setContents(next, Board::CellContents::Empty);

            board.setContents(getOpenLocation(), Board::CellContents::Obstacle);
            board.setContents(getOpenLocation(), Board::CellContents::Food);

            speedUp();
        }
    }
}

void Game::ComposeFrame() {

    board.drawBorder();
    board.drawObstacles();

    if (!game_started) {
        drawTitle();
        return;
    }

    snake.draw(board);

    if (game_over) {
        drawGameOver();
    }
}

Location Game::getOpenLocation() {

    std::uniform_int_distribution<> dist_x(0, board.gridWidth() - 1);
    std::uniform_int_distribution<> dist_y(0, board.gridHeight() - 1);

    Location new_loc;

    while (1) {

        new_loc.x = dist_x(rng);
        new_loc.y = dist_y(rng);

        if (!isOpenLocation(new_loc)) {
            continue;
        }

        return new_loc;
    }
}

bool Game::isOpenLocation(Location const &loc) {

    if (snake.contains(loc)) {
        return false;
    }

    return board.getContents(loc) == Board::CellContents::Empty;
}

void Game::speedUp() {

    if (snake_move_threshold > 0.01) {
        snake_move_threshold -= 0.01;
    }
}

void Game::drawTitle() {

    int x = (gfx.ScreenWidth - 213) / 2;
    int y = (gfx.ScreenHeight - 160) / 2;

    SpriteCodex::DrawTitle(x, y, gfx);
}

void Game::drawGameOver() {

    int x = (gfx.ScreenWidth - 83) / 2;
    int y = (gfx.ScreenHeight - 63) / 2;

    SpriteCodex::DrawGameOver(x, y, gfx);
}
