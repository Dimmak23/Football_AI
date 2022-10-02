#pragma once

#include "platform_commands.h"
#include "renderer.h"
#include "game_objects.h"
#include "utilities.h"
#include "physics.h"

static void simulate_game_session(const Input& keys, Render_State& state, const float& d_time)
{
	clear_screen(reinterpret_cast<u32*>(state.memory), state.height, state.width, 0x808080);

	//Draw PLAYER score
	draw_score(state, player_scored_times/10, 1, true);//draw first digit of the score
	draw_score(state, player_scored_times, 1);//draw second digit of the score
	//Draw PC score
	draw_score(state, pc_scored_times/10, -1, true);//draw first digit of the score
	draw_score(state, pc_scored_times, -1);//draw second digit of the score

	//draw field
	draw_field(state);

	//CALCULATIONS

	//#0
	//Hold on PLAYER accelerations before getting NEW user response
	update_kinematics(player_m, 1);

	//Hold on PC accelerations before getting NEW PC response
	update_kinematics(pc_m, 1);

	//Hold on BALL accelerations before it colide with something NEW
	update_kinematics(ball_m, 1);

	//Check if it is a goal - wait 3 seconds
	_await_for_goal_celebration(d_time);

	//Check if there is a glitch
	//_await_for_glitch(d_time);

	//#1 Need to recalculate BALL colisions before others
	//BALL collisions with PLAYER
	ball_to_rocket_collision(player_rocket, player_c, player_m);
	//BALL collisions with PC
	ball_to_rocket_collision(pc_rocket, pc_c, pc_m);

	//#2 Change acceleration of USER and PC
	// 
	//Re-calculate PLAYER acceleration according to the user response
	accelerate_by_user(keys, player_m, 0);

	//Re-calculate PC acceleration according to the PC response
	//accelerate_by_user(keys, pc_m, 4);

	//Turn on AI to generate command of PC movements
	invoke_ai();

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
		state.memory,
		player_c.pos_x, player_c.pos_y, player_rocket.half_size_x, player_rocket.half_size_y,
		static_cast<float>(state.width), static_cast<float>(state.height),
		player_rocket.color
	);

	//draw PC rocket
	draw_rectangle(
		state.memory,
		pc_c.pos_x, pc_c.pos_y, pc_rocket.half_size_x, pc_rocket.half_size_y,
		static_cast<float>(state.width), static_cast<float>(state.height),
		pc_rocket.color
	);

	//draw the ball
	draw_rectangle(
		state.memory,
		ball_c.pos_x, ball_c.pos_y, ball.half_size_x, ball.half_size_y,
		static_cast<float>(state.width), static_cast<float>(state.height),
		ball.color
	);

}
