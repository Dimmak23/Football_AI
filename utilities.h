#pragma once

//#include "typenames.h"

// Render utilities
static const float render_scale = 0.01f;

inline const float& clamp(const float& minimum, const float& value, const float& maximum) {
	if (value < minimum) return minimum;
	else if (value > maximum) return maximum;
	else return value;
}

// Time utilities
static const float speed{ 50.0 }; // 50 units per second
