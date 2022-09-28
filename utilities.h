#pragma once

//#include "typenames.h"

static const float render_scale = 0.01;

inline const int& clamp(const int& minimum, const int& value, const int& maximum) {
	if (value < minimum) return minimum;
	else if (value > maximum) return maximum;
	else return value;
}
