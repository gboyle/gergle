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
      snake({2, 2}),
      goal(rng, board, snake) {
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

        if (!board.isInside(next) || snake.isInTileExceptEnd(next)) {

            game_over = true;

        } else {

            bool eating = next == goal.getLocation();

            if (eating) {
                snake.grow();
            }

            snake.moveBy(delta);

            if (eating) {
                goal.respawn(rng, board, snake);
            }
        }
    }
}

void Game::ComposeFrame() {

    goal.draw(board);
    snake.draw(board);

    if (game_over) {
        SpriteCodex::DrawGameOver(200, 200, gfx);
    }
}
