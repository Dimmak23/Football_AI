#pragma once

#include "platform_commands.h"
#include "renderer.h"
#include "game_objects.h"
#include "utilities.h"

#define _down(B) keys->buttons.at(B).is_down
#define _pressed(B) keys->buttons.at(B).is_down && keys->buttons.at(B).changed
#define _released(B) !(keys->buttons.at(B).is_down) && keys->buttons.at(B).changed

static void simulate_game_session(Input* keys, Render_State* state, const float& d_time)
{
	clear_screen(reinterpret_cast<u32*>(state->memory), state->height, state->width, 0xff0000);

	if (_down(BUTTON_UP))
		player_coordinates.pos_y += speed * d_time;
	else if(_down(BUTTON_DOWN))
		player_coordinates.pos_y -= speed * d_time;
	else if(_down(BUTTON_RIGHT))
		player_coordinates.pos_x += speed * d_time;
	else if(_down(BUTTON_LEFT))
		player_coordinates.pos_x -= speed * d_time;

	draw_rectangle(
		state->memory,
		player_coordinates.pos_x, player_coordinates.pos_y, player_rocket.rocket_width, player_rocket.rocket_height,
		static_cast<float>(state->width), static_cast<float>(state->height),
		0x0a54d0
	);
}
