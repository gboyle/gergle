
#include "frame-rate.h"

using namespace std::chrono;

FrameRate::FrameRate()
{
	previous = steady_clock::now();
}

float FrameRate::mark()
{
	const auto next = steady_clock::now();

	const duration<float> elapsed = next - previous;

	previous = next;

	return elapsed.count();
}
