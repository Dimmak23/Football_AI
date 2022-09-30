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

	//draw the ball
	draw_rectangle(
		state->memory,
		ball_coordinates.pos_x, ball_coordinates.pos_y, ball.half_size_x, ball.half_size_y,
		static_cast<float>(state->width), static_cast<float>(state->height),
		ball.color
	);

	//CALCULATIONS

	//#1
	//Hold on PLAYER accelerations before getting NEW user response
	player_move.active_acceleration_x = 0.0;
	player_move.active_acceleration_y = 0.0;

	//Hold on PC accelerations before getting NEW PC response
	pc_move.active_acceleration_x = 0.0;
	pc_move.active_acceleration_y = 0.0;

	//#2
	//Re-calculate PLAYER acceleration according to the user response
	if (_down(BUTTON_UP))
		player_move.active_acceleration_y += player_move.acceleration_step;
	else if(_down(BUTTON_DOWN))
		player_move.active_acceleration_y -= player_move.acceleration_step;
	else if(_down(BUTTON_RIGHT))
		player_move.active_acceleration_x += player_move.acceleration_step;
	else if(_down(BUTTON_LEFT))
		player_move.active_acceleration_x -= player_move.acceleration_step;

	//Re-calculate PC acceleration according to the PC response
	if (_down(BUTTON_W))
		pc_move.active_acceleration_y += pc_move.acceleration_step;
	else if(_down(BUTTON_S))
		pc_move.active_acceleration_y -= pc_move.acceleration_step;
	else if(_down(BUTTON_D))
		pc_move.active_acceleration_x += pc_move.acceleration_step;
	else if(_down(BUTTON_A))
		pc_move.active_acceleration_x -= pc_move.acceleration_step;

	//#3
	//Re-calculate PLAYER acceleration according to new acceleration, new speed and friction
	player_move.active_acceleration_x -= player_move.active_speed_x * player_move.friction_coeff;
	player_move.active_acceleration_y -= player_move.active_speed_y * player_move.friction_coeff;

	//Re-calculate PC acceleration according to new acceleration, new speed and friction
	pc_move.active_acceleration_x -= pc_move.active_speed_x * pc_move.friction_coeff;
	pc_move.active_acceleration_y -= pc_move.active_speed_y * pc_move.friction_coeff;

	//#4
	//Re-calculate PLAYER position of the rocket
	player_coordinates.pos_x += player_move.active_speed_x * d_time + player_move.active_acceleration_x * d_time * d_time * 0.5;
	player_coordinates.pos_y += player_move.active_speed_y * d_time + player_move.active_acceleration_y * d_time * d_time * 0.5;

	//Re-calculate PC position of the rocket
	pc_coordinates.pos_x += pc_move.active_speed_x * d_time + pc_move.active_acceleration_x * d_time * d_time * 0.5;
	pc_coordinates.pos_y += pc_move.active_speed_y * d_time + pc_move.active_acceleration_y * d_time * d_time * 0.5;

	//#5
	///!! Re-calculate PLAYER speed for the next cycle - only now you can do this
	player_move.active_speed_x += player_move.active_acceleration_x * d_time;
	player_move.active_speed_y += player_move.active_acceleration_y * d_time;

	///!! Re-calculate PC speed for the next cycle - only now you can do this
	pc_move.active_speed_x += pc_move.active_acceleration_x * d_time;
	pc_move.active_speed_y += pc_move.active_acceleration_y * d_time;

	//#6 Colison detection
	//PLAYER
	if ((player_coordinates.pos_x + player_rocket.half_size_x) > arena.half_size_x)
	{
		player_coordinates.pos_x = arena.half_size_x - player_rocket.half_size_x;
		player_move.active_speed_x *= player_move.collision_bounce_coeff;
	}
	else if ((player_coordinates.pos_x - player_rocket.half_size_x) < -arena.half_size_x)
	{
		player_coordinates.pos_x = -arena.half_size_x + player_rocket.half_size_x;
		//player_coordinates.pos_x = arena.half_size_x + player_rocket.half_size_x; // we can appear on the opposite side of the field
		player_move.active_speed_x *= player_move.collision_bounce_coeff;
	}
	else if ((player_coordinates.pos_y + player_rocket.half_size_y) > arena.half_size_y)
	{
		player_coordinates.pos_y = arena.half_size_y - player_rocket.half_size_y;
		player_move.active_speed_y *= player_move.collision_bounce_coeff;
	}
	else if ((player_coordinates.pos_y - player_rocket.half_size_y) < -arena.half_size_y)
	{
		player_coordinates.pos_y = -arena.half_size_y + player_rocket.half_size_y;
		player_move.active_speed_y *= player_move.collision_bounce_coeff;
	}

	//PC
	if ((pc_coordinates.pos_x + pc_rocket.half_size_x) > arena.half_size_x)
	{
		pc_coordinates.pos_x = arena.half_size_x - pc_rocket.half_size_x;
		pc_move.active_speed_x *= player_move.collision_bounce_coeff;
	}
	else if ((pc_coordinates.pos_x - pc_rocket.half_size_x) < -arena.half_size_x)
	{
		pc_coordinates.pos_x = -arena.half_size_x + pc_rocket.half_size_x;
		pc_move.active_speed_x *= player_move.collision_bounce_coeff;
	}
	else if ((pc_coordinates.pos_y + pc_rocket.half_size_y) > arena.half_size_y)
	{
		pc_coordinates.pos_y = arena.half_size_y - pc_rocket.half_size_y;
		pc_move.active_speed_y *= player_move.collision_bounce_coeff;
	}
	else if ((pc_coordinates.pos_y - pc_rocket.half_size_y) < -arena.half_size_y)
	{
		pc_coordinates.pos_y = -arena.half_size_y + pc_rocket.half_size_y;
		pc_move.active_speed_y *= player_move.collision_bounce_coeff;
	}

	//BALL
	

	//draw PLAYER rocket
	draw_rectangle(
		state->memory,
		player_coordinates.pos_x, player_coordinates.pos_y, player_rocket.half_size_x, player_rocket.half_size_y,
		static_cast<float>(state->width), static_cast<float>(state->height),
		player_rocket.color
	);

	//draw PC rocket
	draw_rectangle(
		state->memory,
		pc_coordinates.pos_x, pc_coordinates.pos_y, pc_rocket.half_size_x, pc_rocket.half_size_y,
		static_cast<float>(state->width), static_cast<float>(state->height),
		pc_rocket.color
	);
}
