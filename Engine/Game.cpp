/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
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
}

void Game::Go() {
    gfx.BeginFrame();
    UpdateModel();
    ComposeFrame();
    gfx.EndFrame();
}

void Game::UpdateModel() {

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

    --snake_move_counter;

    if (snake_move_counter <= 0) {

        snake_move_counter = snake_move_period;

        const Location next = snake.getNextHead(delta);

        bool growing = goal.contains(next);

        if (!board.contains(next) || snake.contains(next, growing) ||
            obstacle.contains(next)) {

            game_over = true;

        } else {

            if (growing) {
                snake.grow();
            }

            snake.moveBy(delta);

            if (growing) {

                obstacle.grow(getOpenLocation());
                goal.respawn(getOpenLocation());

                if (snake_move_period > 1) {
                    --snake_move_period;
                }
            }
        }
    }
}

void Game::ComposeFrame() {

    board.drawBorder();

    if (!game_started) {
        drawTitle();
        return;
    }

    obstacle.draw(board);
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

        if (snake.contains(new_loc)) {
            continue;
        }

        if (obstacle.contains(new_loc)) {
            continue;
        }

        if (goal.contains(new_loc)) {
            continue;
        }

        return new_loc;
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