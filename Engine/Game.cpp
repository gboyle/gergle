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
    goal.respawn(getOpenLocation());

    int poison_count = board.gridWidth() * board.gridWidth() / 4;
    for (int i = 0; i < poison_count; ++i) {
        Location loc = getOpenLocation();
        board.setObstacle(loc, 'P');
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

        bool growing = goal.contains(next);

        if (!board.contains(next) || snake.contains(next, growing)) {
            game_over = true;
            return;
        }

        char obstacle = board.checkForObstacle(next);

        if (obstacle == 'X') {
            game_over = true;
            return;
        }

        if (obstacle == 'P') {
            speedUp();
            // board.setObstacle(next, 0);
        }

        if (growing) {
            snake.grow();
        }

        snake.moveBy(delta);

        if (growing) {

            board.setObstacle(getOpenLocation(), 'X');
            goal.respawn(getOpenLocation());
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

    goal.draw(board);
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

    if (board.checkForObstacle(loc)) {
        return false;
    }

    if (goal.contains(loc)) {
        return false;
    }
    return true;
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
