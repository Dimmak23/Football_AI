#pragma once

#include "game_objects.h"

static bool goal_status{ false };
static bool player_scored{ true };
static float goal_await{ 0.0 };
static const float goal_celebration{ 1.5 };
static int player_scored_times{0};
static int pc_scored_times{0};
static bool score_is_changed{ false };

static float glitch_await{ 0.0 };
static const float glitch_time{ 1.5 };

#define _down(B) keys.buttons.at(B).is_down
#define _pressed(B) keys.buttons.at(B).is_down && keys.buttons.at(B).changed
#define _released(B) !(keys.buttons.at(B).is_down) && keys.buttons.at(B).changed

static void ball_to_rocket_collision(
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
		ball_m.active_speed_x = ball_m.active_speed_x * ball_m.collision_bounce_coeff + p_move.active_speed_x * speed_mult;
		ball_m.active_speed_y = - ball_m.active_speed_y * ball_m.collision_bounce_coeff + p_move.active_speed_y * speed_mult;
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
		ball_m.active_speed_x = ball_m.active_speed_x * ball_m.collision_bounce_coeff + p_move.active_speed_x * speed_mult;
		ball_m.active_speed_y = -ball_m.active_speed_y * ball_m.collision_bounce_coeff + p_move.active_speed_y * speed_mult;
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
		ball_m.active_speed_x = -ball_m.active_speed_x * ball_m.collision_bounce_coeff + p_move.active_speed_x * speed_mult;
		ball_m.active_speed_y = ball_m.active_speed_y * ball_m.collision_bounce_coeff + p_move.active_speed_y * speed_mult;
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
		ball_m.active_speed_x = -ball_m.active_speed_x * ball_m.collision_bounce_coeff + p_move.active_speed_x * speed_mult;
		ball_m.active_speed_y = ball_m.active_speed_y * ball_m.collision_bounce_coeff + p_move.active_speed_y * speed_mult;
	}
}

static void _to_wall_collision(
	const tools& body,
	coordinates& p_coor,
	movements& p_move,
	const bool& t_ball, // true for the BALL, false for PLAYER or PC
	const bool& player_or_pc = false // true - PLAYER, false - PC
)
{
	if ((p_coor.pos_x + body.half_size_x) > (player_or_pc || t_ball) * arena.half_size_x)
	{
		if (
			((p_coor.pos_y - body.half_size_y) >= -gate.half_size_y)
			&&
			((p_coor.pos_y + body.half_size_y) <= gate.half_size_y)
			&&
			t_ball
			)
		{
			if ((p_coor.pos_x - body.half_size_x) > arena.half_size_x)
			{
				goal_status = true;
				player_scored = false;

				//We say that we need to change score
				if(!score_is_changed)
				{
					pc_scored_times++;
					score_is_changed = true;//we will never change score until NEW ball will be thrown
				}

				p_move.active_speed_x *= speed_loss;
				p_move.active_speed_y *= speed_loss;
			}
			if ((p_coor.pos_x + body.half_size_x) > (arena.half_size_x + 3 * std_half_width + 2 * gate.half_size_x))
			{
				p_coor.pos_x = arena.half_size_x + 3.25 * std_half_width + 2 * gate.half_size_x - body.half_size_x;
				p_move.active_speed_x = 0;
				p_move.active_speed_y = 0;
			}
		}
		else
		{
			p_coor.pos_x = (player_or_pc || t_ball) * arena.half_size_x - body.half_size_x;
			p_move.active_speed_x *= p_move.collision_bounce_coeff;
		}
	}
	if ((p_coor.pos_x - body.half_size_x) < -(!player_or_pc || t_ball) * arena.half_size_x)
	{
		if (
			((p_coor.pos_y - body.half_size_y) >= -gate.half_size_y)
			&&
			((p_coor.pos_y + body.half_size_y) <= gate.half_size_y)
			&&
			t_ball
			)
		{
			if ((p_coor.pos_x + body.half_size_x) < -arena.half_size_x)
			{
				goal_status = true;
				player_scored = true;
				
				//We say that we need to change score
				if (!score_is_changed)
				{
					player_scored_times++;
					score_is_changed = true;//we will never change score until NEW ball will be thrown
				}

				p_move.active_speed_x *= speed_loss;
				p_move.active_speed_y *= speed_loss;
			}
			if ((p_coor.pos_x - body.half_size_x) < -(arena.half_size_x + 3 * std_half_width + 2 * gate.half_size_x))
			{
				p_coor.pos_x = - arena.half_size_x - 3.25 * std_half_width - 2 * gate.half_size_x + body.half_size_x;
				p_move.active_speed_x = 0;
				p_move.active_speed_y = 0;
			}
		}
		else
		{
			p_coor.pos_x = -(!player_or_pc || t_ball) * arena.half_size_x + body.half_size_x;
			//p_coor.pos_x = arena.half_size_x + body.half_size_x; // we can appear on the opposite side of the field
			p_move.active_speed_x *= p_move.collision_bounce_coeff;
		}
	}
	if ((p_coor.pos_y + body.half_size_y) > arena.half_size_y)
	{
		p_coor.pos_y = arena.half_size_y - body.half_size_y;
		p_move.active_speed_y *= p_move.collision_bounce_coeff;
	}
	if ((p_coor.pos_y - body.half_size_y) < -arena.half_size_y)
	{
		p_coor.pos_y = -arena.half_size_y + body.half_size_y;
		p_move.active_speed_y *= p_move.collision_bounce_coeff;
	}
}

static void kinematics(
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

static void update_kinematics(movements& peer, const int& sign_for_x, const bool& option = false) // option false - we just update accelerations
{
	if (option)
	{
		peer.active_speed_x = sign_for_x * peer.null_speed;
		peer.active_speed_y = peer.null_speed;
	}
	peer.active_acceleration_x = sign_for_x * peer.null_acceleration;
	peer.active_acceleration_y = peer.null_acceleration;
}

static void accelerate_by_user(const Input& keys, movements& peer, const int& keyboard_offset)
{
	//Re-calculate PEER acceleration according to the user response
	if (_down(keyboard_offset + BUTTON_UP))
	{
		peer.active_acceleration_y += peer.acceleration_step;
		peer.active_speed_y += peer.null_speed;
	}
	else if (_down(keyboard_offset + BUTTON_DOWN))
	{
		peer.active_acceleration_y -= peer.acceleration_step;
		peer.active_speed_y -= peer.null_speed;
	}
	else if (_down(keyboard_offset + BUTTON_RIGHT))
	{
		peer.active_acceleration_x += peer.acceleration_step;
		peer.active_speed_x += peer.null_speed;
	}
	else if (_down(keyboard_offset + BUTTON_LEFT))
	{
		peer.active_acceleration_x -= peer.acceleration_step;
		peer.active_speed_x -= peer.null_speed;
	}
}

static void invoke_ai()
{
	//behavior while ball on the PC field
	if (ball_c.pos_x < 0)
	{
		//PC rocket on the LEFT from the ball
		if (((pc_c.pos_x + pc_rocket.half_size_x) < (ball_c.pos_x - ball.half_size_x)))
		{
			//PC on the left above the ball
			if ((pc_c.pos_y - pc_rocket.half_size_y) > (ball_c.pos_y + ball.half_size_y))
			{
				pc_m.active_acceleration_y -= pc_m.acceleration_step;
				pc_m.active_acceleration_x += 0.25 * pc_m.acceleration_step;
			}
			//PC on the left under the ball
			else if ((pc_c.pos_y + pc_rocket.half_size_y) < (ball_c.pos_y - ball.half_size_y))
			{
				pc_m.active_acceleration_y += pc_m.acceleration_step;
				pc_m.active_acceleration_x += 0.25 * pc_m.acceleration_step;
			}
			//PC rocket cover the ball -- heat by the X axis
			else
			{
				if(player_c.pos_y>0)
					//if PLAYER on the UPPER side -- add acceleration to DOWN side
					pc_m.active_acceleration_y -= 0.5 * pc_m.acceleration_step;
				else 
					//if PLAYER on the DOWN side -- add acceleration to UPPER side
					pc_m.active_acceleration_y += 0.5 * pc_m.acceleration_step;
				//hit by X axis
				pc_m.active_acceleration_x += pc_m.acceleration_step;
			}
		}
		//PC rocket on the RIGHT from the ball
		else if (((pc_c.pos_x - pc_rocket.half_size_x) > (ball_c.pos_x + ball.half_size_x)))
		{
			//PC rocket cover ball
			if (
				((ball_c.pos_y + ball.half_size_y) <= (pc_c.pos_y + pc_rocket.half_size_y))
				&&
				((ball_c.pos_y - ball.half_size_y) >= (pc_c.pos_y - pc_rocket.half_size_y))
				)
			{
				pc_m.active_speed_x = 0;
				pc_m.active_acceleration_x = 0;
				if (pc_c.pos_y > 0)
					pc_m.active_acceleration_y -= 8 * pc_m.acceleration_step;
				else
					pc_m.active_acceleration_y += 8 * pc_m.acceleration_step;
			}
			//PC rocket no loger cover the ball
			else
			{
				//pc_m.active_speed_x = - pc_m.null_speed;
				pc_m.active_acceleration_x -= 4 * pc_m.acceleration_step;
			}
		}
		//PC ABOVE or UNDER the ball and can touch the ball
		else 
		{
			//PC ABOVE the ball
			if ((pc_c.pos_y - pc_rocket.half_size_y) > (ball_c.pos_y + ball.half_size_y))
				pc_m.active_acceleration_y -= pc_m.acceleration_step;
			//PC UNDER the ball
			else 
	 			pc_m.active_acceleration_y += pc_m.acceleration_step;
		}
	}
	//behavior while ball on the PLAYER's field
	else
	{
		if (pc_c.pos_x > pc_c.init_x)
			pc_m.active_acceleration_x -= 0.5 * pc_m.acceleration_step;
		else
			pc_m.active_acceleration_x += 0.5 * pc_m.acceleration_step;

		if (pc_c.pos_y > pc_c.init_y)
			pc_m.active_acceleration_y -= 0.5 * pc_m.acceleration_step;
		else
			pc_m.active_acceleration_y += 0.5 * pc_m.acceleration_step;

		if (
			goal_status
			||
			(pc_c.pos_x > (pc_c.init_x - 0.5))
			&&
			(pc_c.pos_x < (pc_c.init_x + 0.5))
			&&
			(pc_c.pos_y < (pc_c.init_y + 0.5))
			&&
			(pc_c.pos_y > (pc_c.init_y - 0.5))
			) 
		{
			pc_m.active_speed_x *= 0.01;
			pc_m.active_acceleration_x = 0;
			pc_m.active_speed_y *= 0.01;
			pc_m.active_acceleration_y = 0;

		}
	}

}
