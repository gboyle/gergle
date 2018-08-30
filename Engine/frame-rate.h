#pragma once

#include <chrono>

class FrameRate {

	std::chrono::steady_clock::time_point previous;

public:

	FrameRate();

	float mark();
};
