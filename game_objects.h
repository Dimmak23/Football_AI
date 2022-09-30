#pragma once

//Positions

struct coordinates
{
	float pos_x, pos_y;

}
player_c{ 80.0, 0.0 },
pc_c{ -80.0, 0.0 },
ball_c{ 0.0, 0.0 };

struct tools
{
	float half_size_x{}, half_size_y{};
	u32 color{};

}
const player_rocket{ 1.0, 6.0, 0x0a54d0 },
pc_rocket{ 1.0, 6.0, 0xd31262 },
ball{ 1.0, 1.0, 0x00ff00 };

struct util_rectangle
{
	float initial_position_x{}, initial_position_y{};
	float half_size_x{}, half_size_y{};
	u32 color{};

}
const arena{ 0, 0, 85, 45, 0xffaa33 },
center_line{ 0, 0, 0.1, 45, 0x000000 };

//Movement

struct movements
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
player_m{ 0.0, 0.0, 2000.0, 10.0, -0.5, 0.0, 0.0, 0.0, 0.0 },
pc_m{ 0.0, 0.0, 3000.0, 10.0, -0.5, 0.0, 0.0, 0.0, 0.0 },
ball_m{ 0.0, 0.0, 2000.0, 1.0, -0.98, 70.0, 1000.0, 70.0, 1000.0 };
