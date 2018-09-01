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

#pragma once

#include "Graphics.h"
#include "Keyboard.h"
#include "Mouse.h"

#include "board.h"
#include "frame-rate.h"
#include "goal.h"
#include "snake.h"

#include <random>

class Game {
  public:
    Game(class MainWindow &wnd);
    Game(const Game &) = delete;
    Game &operator=(const Game &) = delete;
    void Go();

  private:
    void ComposeFrame();
    void UpdateModel();
    /********************************/
    /*  User Functions              */
    /********************************/
  private:
    MainWindow &wnd;
    Graphics gfx;
    /********************************/
    /*  User Variables              */
    /********************************/

    std::mt19937 rng;

    Board board;
    Snake snake;
    Goal goal;

    Location delta = {1, 0};

    float snake_move_threshold = 0.3f;
    float snake_move_elapsed = 0.0f;

    bool game_started = false;
    bool game_over = false;

    FrameRate frame_rate;

    Location getOpenLocation();
    bool isOpenLocation(Location const &loc);

    void speedUp();

    void drawTitle();
    void drawGameOver();
};
