#pragma once

#include "platform_commands.h"
#include "renderer.h"
#include "game_objects.h"
#include "utilities.h"
#include "physics.h"

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

	//draw center line
	draw_rectangle(
		state->memory,
		center_line.initial_position_x, center_line.initial_position_y, center_line.half_size_x, center_line.half_size_y,
		static_cast<float>(state->width), static_cast<float>(state->height),
		center_line.color
	);

	//CALCULATIONS

	//#0
	//Hold on PLAYER accelerations before getting NEW user response
	player_m.active_acceleration_x = player_m.null_acceleration;
	player_m.active_acceleration_y = player_m.null_acceleration;

	//Hold on PC accelerations before getting NEW PC response
	pc_m.active_acceleration_x = pc_m.null_acceleration;
	pc_m.active_acceleration_y = pc_m.null_acceleration;

	//Hold on BALL accelerations before it colide with something NEW
	ball_m.active_acceleration_x = ball_m.null_acceleration;
	ball_m.active_acceleration_y = ball_m.null_acceleration;

	//#1 Need to recalculate BALL colisions before others

	//BALL collisions with PLAYER
	ball_to_rocket_collision(player_rocket, player_c, player_m);
	//BALL collisions with PC
	ball_to_rocket_collision(pc_rocket, pc_c, pc_m);

	//#2 Change acceleration of USER and PC
	// 
	//Re-calculate PLAYER acceleration according to the user response
	if (_down(BUTTON_UP))
		player_m.active_acceleration_y += player_m.acceleration_step;
	else if(_down(BUTTON_DOWN))
		player_m.active_acceleration_y -= player_m.acceleration_step;
	else if(_down(BUTTON_RIGHT))
		player_m.active_acceleration_x += player_m.acceleration_step;
	else if(_down(BUTTON_LEFT))
		player_m.active_acceleration_x -= player_m.acceleration_step;

	//Re-calculate PC acceleration according to the PC response
	if (_down(BUTTON_W))
		pc_m.active_acceleration_y += pc_m.acceleration_step;
	else if(_down(BUTTON_S))
		pc_m.active_acceleration_y -= pc_m.acceleration_step;
	else if(_down(BUTTON_D))
		pc_m.active_acceleration_x += pc_m.acceleration_step;
	else if(_down(BUTTON_A))
		pc_m.active_acceleration_x -= pc_m.acceleration_step;

	//Kinematics re-calculations for PLAYER
	kinematics(player_c, player_m, d_time);
	//Kinematics re-calculations for PC
	kinematics(pc_c, pc_m, d_time);
	//Kinematics re-calculations for BALL
	kinematics(ball_c, ball_m, d_time);

	//#6 Colison detection
	//PLAYER collisions with ARENA
	_to_wall_collision(player_rocket, player_c, player_m, false, true);
	//PC collisions with ARENA
	_to_wall_collision(pc_rocket, pc_c, pc_m, false, false);
	//BALL collisions with ARENA
	_to_wall_collision(ball, ball_c, ball_m, true);

	//draw PLAYER rocket
	draw_rectangle(
		state->memory,
		player_c.pos_x, player_c.pos_y, player_rocket.half_size_x, player_rocket.half_size_y,
		static_cast<float>(state->width), static_cast<float>(state->height),
		player_rocket.color
	);

	//draw PC rocket
	draw_rectangle(
		state->memory,
		pc_c.pos_x, pc_c.pos_y, pc_rocket.half_size_x, pc_rocket.half_size_y,
		static_cast<float>(state->width), static_cast<float>(state->height),
		pc_rocket.color
	);

	//draw the ball
	draw_rectangle(
		state->memory,
		ball_c.pos_x, ball_c.pos_y, ball.half_size_x, ball.half_size_y,
		static_cast<float>(state->width), static_cast<float>(state->height),
		ball.color
	);
}
