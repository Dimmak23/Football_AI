#pragma once

//Positions

struct game_coordinates
{
	float pos_x, pos_y;

} player_coordinates{ 80.0, 0.0 }, pc_coordinates{ -80.0, 0.0 }, ball_coordinates{ 0.0, 0.0 };

struct tools
{
	float half_size_x{}, half_size_y{};
	u32 color{};

}
const player_rocket{ 1.0, 6.0, 0x0a54d0 },
pc_rocket{ 1.0, 6.0, 0xd31262 },
ball{ 1.0, 1.0, 0x00ff00 };

struct big_rectangle
{
	int initial_position_x{}, initial_position_y{};
	int half_size_x{}, half_size_y{};
	u32 color{};

}
const arena{0, 0, 85, 45, 0xffaa33};

//Movement

struct movement_parameters
{
	const float null_speed{};
	const float null_acceleration{};
	const float acceleration_step{};
	const float friction_coeff{};
	const float collision_bounce_coeff{};
	float active_speed_x{};
	float active_acceleration_x{};
	float active_speed_y{};
	float active_acceleration_y{};

}
player_move{ 0.0, 0.0, 6000.0, 10.0, -0.5, 0.0, 0.0, 0.0, 0.0 },
pc_move{ 0.0, 0.0, 5000.0, 10.0, -0.5, 0.0, 0.0, 0.0, 0.0 },
ball_move{ 0.0, 0.0, 7000.0, 10.0, -2, 0.0, 0.0, 0.0, 0.0 };
