#pragma once

struct game_coordinates
{
	float pos_x, pos_y;
} player_coordinates{ 80.0, 0.0 }, pc_coordinates{ -80.0, 0.0 }, ball_coordinates{ 0.0, 0.0 };

struct tools
{
	float half_size_x{}, half_size_y{};
	u32 color{};
} const player_rocket{ 1.0, 6.0, 0x0a54d0 }, pc_rocket{ 1.0, 6.0, 0xd31262 }, ball{ 1.0, 1.0, 0x00ff00 };

struct big_rectangle
{
	int initial_position_x{}, initial_position_y{};
	int half_size_x{}, half_size_y{};
	u32 color{};
} const arena{0, 0, 85, 45, 0xffaa33};