#pragma once

#include "platform_commands.h"
#include "renderer.h"
#include "game_objects.h"
#include "utilities.h"

#include <iostream>

#define _down(B) keys->buttons.at(B).is_down
#define _pressed(B) keys->buttons.at(B).is_down && keys->buttons.at(B).changed
#define _released(B) !(keys->buttons.at(B).is_down) && keys->buttons.at(B).changed

static void simulate_game_session(Input* keys, Render_State* state, const float& d_time)
{
	clear_screen(reinterpret_cast<u32*>(state->memory), state->height, state->width, 0xff0000);

	//draw arena
	draw_rectangle(
		state->memory,
		arena.initial_position_x, arena.initial_position_y,arena.half_size_x,arena.half_size_y,
		static_cast<float>(state->width), static_cast<float>(state->height),
		arena.color
	);

	//draw PC rocket
	draw_rectangle(
		state->memory,
		pc_coordinates.pos_x, pc_coordinates.pos_y, pc_rocket.half_size_x, pc_rocket.half_size_y,
		static_cast<float>(state->width), static_cast<float>(state->height),
		pc_rocket.color
	);

	//draw the ball
	draw_rectangle(
		state->memory,
		ball_coordinates.pos_x, ball_coordinates.pos_y, ball.half_size_x, ball.half_size_y,
		static_cast<float>(state->width), static_cast<float>(state->height),
		ball.color
	);

	if (_down(BUTTON_UP))
		player_coordinates.pos_y += speed * d_time;
	else if(_down(BUTTON_DOWN))
		player_coordinates.pos_y -= speed * d_time;
	else if(_down(BUTTON_RIGHT))
		player_coordinates.pos_x += speed * d_time;
	else if(_down(BUTTON_LEFT))
		player_coordinates.pos_x -= speed * d_time;

	//draw player rocket
	draw_rectangle(
		state->memory,
		player_coordinates.pos_x, player_coordinates.pos_y, player_rocket.half_size_x, player_rocket.half_size_y,
		static_cast<float>(state->width), static_cast<float>(state->height),
		player_rocket.color
	);

}
