#pragma once

//Positions

static const float std_half_width{ 0.1 };

static const float gate_half_sizeX{ 3.0 };
static const float gate_half_sizeY{ 10.0 };

static const float speed_mult{ 2.5 };
static const float speed_loss{ 0.65 };

static const float rocket_init_y{ 0.0 };
static const float rocket_linit_x{ -75.0 };
static const float rocket_rinit_x{ 75.0 };

static struct coordinates
{
	float pos_x, pos_y;

}
player_c{ 75.0, 0.0 },
pc_c{ -75.0, 0.0 },
ball_c{ 0.0, 0.0 };

static struct tools
{
	float half_size_x{}, half_size_y{};
	u32 color{};

}
const player_rocket{ 1.0, 6.0, 0x0a54d0 },
pc_rocket{ 1.0, 6.0, 0xd31262 },
ball{ 1.0, 1.0, 0xffa500 };

static struct util_rectangle
{
	float initial_position_x{}, initial_position_y{};
	float line_width{};
	float half_size_x{}, half_size_y{};
	u32 color{};

}
const arena{ 0.0, 0.0, 0.0, 82.0, 43.0, 0x0b9a6d },
center_line{ 0.0, 0.0, 0.0, std_half_width, arena.half_size_y, 0xffffff },
gate{0.0, 0.0, 0.0, gate_half_sizeX, gate_half_sizeY, 0x000000},
side_lines{ 0.0, 0.0, std_half_width, arena.half_size_x + 2*std_half_width, arena.half_size_y + 2*std_half_width, 0xffffff};

//Movement

static struct movements
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
player_m{ 0.0, 0.0, 4000.0, 28.0, -0.75, 0.0, 0.0, 0.0, 0.0 },
pc_m{ 0.0, 0.0, 4000.0, 28.0, -0.75, 0.0, 0.0, 0.0, 0.0 },
ball_m{ 190.0, 0.0, 8000.0, 1.5, -0.98, -190.0, 1000.0, 190.0, 1000.0 };
