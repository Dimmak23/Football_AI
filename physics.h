#pragma once

#include "game_objects.h"

inline void ball_to_rocket_collision(
	const tools& rocket,
	coordinates& p_coor,
	movements& p_move
)
{
	//RIGHT side of the rocket
	if (
		((ball_c.pos_x - ball.half_size_x) > (p_coor.pos_x - rocket.half_size_x))
		&&
		((ball_c.pos_x - ball.half_size_x) < (p_coor.pos_x + rocket.half_size_x))
		&&
		((ball_c.pos_y + ball.half_size_y) < (p_coor.pos_y + rocket.half_size_y))
		&&
		((ball_c.pos_y - ball.half_size_y) > (p_coor.pos_y - rocket.half_size_y))
		)
	{
		//We supress ball to the RIGHT wall
		if (
			((ball_c.pos_x + ball.half_size_x) == arena.half_size_x)
			)
		{
			p_coor.pos_x = arena.half_size_x - rocket.half_size_x - 2 * ball.half_size_x;
			p_move.active_speed_x *= p_move.collision_bounce_coeff;
		}
		else
		{
			ball_c.pos_x = p_coor.pos_x + rocket.half_size_x + ball.half_size_x;
		}
		ball_m.active_speed_x *= ball_m.collision_bounce_coeff;
		ball_m.active_speed_y *= ball_m.collision_bounce_coeff;
		ball_m.active_speed_x += p_move.active_speed_x * 2;
		ball_m.active_speed_y += p_move.active_speed_y * 2;
	}
	//LEFT side of the rocket
	else if (
		((ball_c.pos_x + ball.half_size_x) > (p_coor.pos_x - rocket.half_size_x))
		&&
		((ball_c.pos_x + ball.half_size_x) < (p_coor.pos_x + rocket.half_size_x))
		&&
		((ball_c.pos_y - ball.half_size_y) < (p_coor.pos_y + rocket.half_size_y))
		&&
		((ball_c.pos_y + ball.half_size_y) > (p_coor.pos_y - rocket.half_size_y))
		)
	{
		//We supress ball to the LEFT wall
		if (
			((ball_c.pos_x - ball.half_size_x) == -arena.half_size_x)
			)
		{
			p_coor.pos_x = -arena.half_size_x + rocket.half_size_x + 2 * ball.half_size_x;
			p_move.active_speed_x *= p_move.collision_bounce_coeff;
		}
		else
		{
			ball_c.pos_x = p_coor.pos_x - rocket.half_size_x - ball.half_size_x;
		}
		ball_m.active_speed_x *= ball_m.collision_bounce_coeff;
		ball_m.active_speed_y *= ball_m.collision_bounce_coeff;
		ball_m.active_speed_x += p_move.active_speed_x * 2;
		ball_m.active_speed_y += p_move.active_speed_y * 2;
	}
	//UP side of the rocket
	else if (
		((ball_c.pos_y - ball.half_size_y) > (p_coor.pos_y - rocket.half_size_y))
		&&
		((ball_c.pos_y - ball.half_size_y) < (p_coor.pos_y + rocket.half_size_y))
		&&
		(
			((ball_c.pos_x + ball.half_size_x) <= (p_coor.pos_x + rocket.half_size_x))
			&&
			((ball_c.pos_x + ball.half_size_x) >= (p_coor.pos_x - rocket.half_size_x))
			||
			((ball_c.pos_x - ball.half_size_x) <= (p_coor.pos_x + rocket.half_size_x))
			&&
			((ball_c.pos_x - ball.half_size_x) >= (p_coor.pos_x - rocket.half_size_x))
			)
		)
	{
		//We supress ball to the UP wall
		if (
			((ball_c.pos_y + ball.half_size_y) == arena.half_size_y)
			)
		{
			p_coor.pos_y = arena.half_size_y - rocket.half_size_y - 2 * ball.half_size_y;
			p_move.active_speed_y *= p_move.collision_bounce_coeff;
		}
		else
		{
			ball_c.pos_y = p_coor.pos_y + rocket.half_size_y + ball.half_size_y;
		}
		ball_m.active_speed_x *= ball_m.collision_bounce_coeff;
		ball_m.active_speed_y *= ball_m.collision_bounce_coeff;
		ball_m.active_speed_x += p_move.active_speed_x * 2;
		ball_m.active_speed_y += p_move.active_speed_y * 2;
	}
	//DOWN side of the rocket
	else if (
		((ball_c.pos_y + ball.half_size_y) > (p_coor.pos_y - rocket.half_size_y))
		&&
		((ball_c.pos_y + ball.half_size_y) < (p_coor.pos_y + rocket.half_size_y))
		&&
		(
			((ball_c.pos_x + ball.half_size_x) <= (p_coor.pos_x + rocket.half_size_x))
			&&
			((ball_c.pos_x + ball.half_size_x) >= (p_coor.pos_x - rocket.half_size_x))
			||
			((ball_c.pos_x - ball.half_size_x) <= (p_coor.pos_x + rocket.half_size_x))
			&&
			((ball_c.pos_x - ball.half_size_x) >= (p_coor.pos_x - rocket.half_size_x))
			)
		)
	{
		//We supress ball to the DOWN wall
		if (
			((ball_c.pos_y - ball.half_size_y) == -arena.half_size_y)
			)
		{
			p_coor.pos_y = -arena.half_size_y + rocket.half_size_y + 2 * ball.half_size_y;
			p_move.active_speed_y *= p_move.collision_bounce_coeff;
		}
		else
		{
			ball_c.pos_y = p_coor.pos_y - rocket.half_size_y - ball.half_size_y;
		}
		ball_m.active_speed_x *= ball_m.collision_bounce_coeff;
		ball_m.active_speed_y *= ball_m.collision_bounce_coeff;
		ball_m.active_speed_x += p_move.active_speed_x * 2;
		ball_m.active_speed_y += p_move.active_speed_y * 2;
	}
}

inline void _to_wall_collision(
	const tools& rocket,
	coordinates& p_coor,
	movements& p_move,
	const bool& ball, // true for the BALL, false for PLAYER or PC
	const bool& player_or_pc = false // true - PLAYER, false - PC
)
{
	if ((p_coor.pos_x + rocket.half_size_x) > (player_or_pc || ball)*arena.half_size_x)
	{
		p_coor.pos_x = (player_or_pc || ball)*arena.half_size_x - rocket.half_size_x;
		p_move.active_speed_x *= p_move.collision_bounce_coeff;
	}
	if ((p_coor.pos_x - rocket.half_size_x) < -(!player_or_pc || ball) * arena.half_size_x)
	{
		p_coor.pos_x = -(!player_or_pc || ball) * arena.half_size_x + rocket.half_size_x;
		//p_coor.pos_x = arena.half_size_x + rocket.half_size_x; // we can appear on the opposite side of the field
		p_move.active_speed_x *= p_move.collision_bounce_coeff;
	}
	if ((p_coor.pos_y + rocket.half_size_y) > arena.half_size_y)
	{
		p_coor.pos_y = arena.half_size_y - rocket.half_size_y;
		p_move.active_speed_y *= p_move.collision_bounce_coeff;
	}
	if ((p_coor.pos_y - rocket.half_size_y) < -arena.half_size_y)
	{
		p_coor.pos_y = -arena.half_size_y + rocket.half_size_y;
		p_move.active_speed_y *= p_move.collision_bounce_coeff;
	}
}

inline void kinematics(
	coordinates& p_coor,
	movements& p_move,
	const float& d_time
)
{
	//#3 Change of accelerations because of frictions
	//Re-calculate OBJECT acceleration according to new acceleration, new speed and friction
	p_move.active_acceleration_x -= p_move.active_speed_x * p_move.friction_coeff;
	p_move.active_acceleration_y -= p_move.active_speed_y * p_move.friction_coeff;

	//#4
	//Re-calculate OBJECT position of the rocket
	p_coor.pos_x += p_move.active_speed_x * d_time + p_move.active_acceleration_x * d_time * d_time * 0.5;
	p_coor.pos_y += p_move.active_speed_y * d_time + p_move.active_acceleration_y * d_time * d_time * 0.5;

	//#5
	///!! Re-calculate OBJECT speed for the next cycle - only now you can do this
	p_move.active_speed_x += p_move.active_acceleration_x * d_time;
	p_move.active_speed_y += p_move.active_acceleration_y * d_time;

}
