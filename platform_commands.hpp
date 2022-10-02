#pragma once

#include <vector>
#include "typenames.hpp"

struct Button_state
{
	bool is_down{ false };
	bool changed{ false };
};

enum Button_index
{
	//player
	BUTTON_UP = 0,
	BUTTON_DOWN,
	BUTTON_LEFT,
	BUTTON_RIGHT,

	//PC
	BUTTON_W,
	BUTTON_S,
	BUTTON_A,
	BUTTON_D,

	BUTTON_COUNT // would be the last item
};

static struct Input
{
	std::vector<Button_state> buttons;
} user_keyboard;

static void response_convert(const u32& key_code, const bool& key_state, const int& expected, Button_state& from_keyboard)
{
	if (key_code == expected)
	{
		from_keyboard.changed = (from_keyboard.is_down != key_state);
		from_keyboard.is_down = key_state;
	}
}