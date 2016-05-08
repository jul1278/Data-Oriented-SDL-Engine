#pragma once
#include <algorithm>
#include <iostream>

int randInt(int left, int right, int step = 1) { 

	if (left > right)
		std::swap(left, right);

	if (step <= 0 || left == right || abs(left) + abs(right) < step)
		return left;

	int aright = abs(right);
	int aleft = abs(left);

	if (aleft > aright)
		std::swap(aleft, aright);

	int r = 1;
	int c = 0;

	if (right <= 0 || left >= 0) { // if the interval is fully negative or fully positive
		left >= 0 ? r = 1 : r = -1;
		r *= rand() % (aright - aleft) + aleft;
	}
	else {
		aright += aleft;
		aleft = 0;
		r *= rand() % (aright - aleft) - abs(left);
		c = abs(left);
	}

	r += c;

	if (rand() % 2) { // round down
		r = (r / step) * step;
		r = std::max(r, left);
	}
	else { // round up
		r = (r / step + 1) * step;
		r = std::min(r, right + c);
	}

	r -= c;

	return r;
}
