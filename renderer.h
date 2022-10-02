#pragma once

#include "utilities.h"
#include "typenames.h"
#include "game_objects.h"
#include "platform_commands.h"

static const float draw_offset{ 0.75 };
static const float cube_s{ 0.25 };

static struct Render_State
{
	int height, width;
	void* memory;

	/*
	The BITMAPINFOHEADER structure contains information
	about the dimensions and color format
	of a device-independent bitmap (DIB).
	*/
	BITMAPINFO bitmap_info;

} render_state;

static bool gameIsRunning = true;

static void clear_screen(u32* source_memory, const int& h, const int& w, const u32& color)
{
	
	for (int screen_px{}; screen_px < h*w; screen_px++) {
			*source_memory++ = color;
	}
}

static void draw_normal_triangle(void* source_memory, float initPosX, float initPosY, float& halfSizeX, float& halfSizeY, const float& maxWidth, const float& maxHeight, const u32& color)
{

	initPosX *= maxHeight * render_scale;
	halfSizeX *= maxHeight * render_scale;
	initPosY *= maxHeight * render_scale;
	halfSizeY *= maxHeight * render_scale;

	initPosX += maxWidth / 2.f;
	initPosY += maxHeight / 2.f;

	float endX = initPosX + halfSizeX;
	float endY = initPosY + halfSizeY;
	initPosX -= halfSizeX;
	initPosY -= halfSizeY;
	
	initPosX = clamp(0, initPosX, maxWidth);
	endX = clamp(0, endX, maxWidth);
	initPosY = clamp(0, initPosY, maxHeight);
	endY = clamp(0, endY, maxHeight);

	int adder{};
	for (int y{ static_cast<int>(initPosY) }; y < static_cast<int>(endY); y++, adder++) {
		u32* pixel = reinterpret_cast<u32*>(source_memory) + static_cast<int>(initPosX) + y * static_cast<int>(maxWidth) + adder;
		for (int x{ static_cast<int>(initPosX) }; x < static_cast<int>(endX)-adder; x++) {
			*pixel++ = color;
		}
	}
}

static void draw_rectangle_in_pixels(void* source_memory, float initPosX, float initPosY, const float& halfSizeX, const float& halfSizeY, const float& maxWidth, const float& maxHeight, const u32& color) {

	//We need to privent going outside of the allocated memory by 'pixel'
	//when moving game window
	/*
	Clamps the specified value to the specified minimum and maximum range
	<return_value> clamp(min, x, max)
	The clamped value for the x parameter.
	*/

	float endX = initPosX + halfSizeX;
	float endY = initPosY + halfSizeY;
	initPosX -= halfSizeX;
	initPosY -= halfSizeY;

	initPosX = clamp(0, initPosX, maxWidth);
	endX = clamp(0, endX, maxWidth);
	initPosY = clamp(0, initPosY, maxHeight);
	endY = clamp(0, endY, maxHeight);

	for (int y{ static_cast<int>(initPosY) }; y < static_cast<int>(endY); y++) {
		u32* pixel = reinterpret_cast<u32*>(source_memory) + static_cast<int>(initPosX) + y * static_cast<int>(maxWidth);
		for (int x{ static_cast<int>(initPosX) }; x < endX; x++) {

			*pixel++ = color;
		}
	}
}

static void draw_rectangle(void* source_memory, float initPosX, float initPosY, float halfSizeX, float halfSizeY, const float& maxWidth, const float& maxHeight, const u32& color)
{

	//Change to pixels
	//Everything multiplied by maxHeight - size of the screen -> when we move width size - nothing change,
	//when we move height size - game window updates
	initPosX *= maxHeight * render_scale;
	halfSizeX *= maxHeight * render_scale;
	initPosY *= maxHeight * render_scale;
	halfSizeY *= maxHeight * render_scale;

	//Let's imply logic to center sprite:

	initPosX += maxWidth / 2.f;
	initPosY += maxHeight / 2.f;

	//Then we sent them to the center of the screen
	draw_rectangle_in_pixels(source_memory, initPosX, initPosY, halfSizeX, halfSizeY, maxWidth, maxHeight, color);
}

static void draw_circle(void* source_memory, float initPosX, float initPosY, float halfSizeX, float halfSizeY, const float& maxWidth, const float& maxHeight, const u32& color)
{
	//Change to pixels
	//Everything multiplied by maxHeight - size of the screen -> when we move width size - nothing change,
	//when we move height size - game window updates
	initPosX *= maxHeight * render_scale;
	halfSizeX *= maxHeight * render_scale;
	initPosY *= maxHeight * render_scale;
	halfSizeY *= maxHeight * render_scale;

	//Let's imply logic to center sprite:

	initPosX += maxWidth / 2.f;
	initPosY += maxHeight / 2.f;

	//Then we sent them to the center of the screen
	float endX = initPosX + halfSizeX;
	float endY = initPosY + halfSizeY;
	initPosX -= halfSizeX;
	initPosY -= halfSizeY;

	initPosX = clamp(0, initPosX, maxWidth);
	endX = clamp(0, endX, maxWidth);
	initPosY = clamp(0, initPosY, maxHeight);
	endY = clamp(0, endY, maxHeight);

	float shaper{0.01f};
	const float shaper_step = 1 / (endX - initPosX);

	for (int y{ static_cast<int>(initPosY) }; y < static_cast<int>(endY); y++) {
		u32* pixel = reinterpret_cast<u32*>(source_memory) + static_cast<int>(initPosX) + y * static_cast<int>(maxWidth);
		for (float x{ initPosX - shaper * ((endX - initPosX) / 2.f) }; x < (endX - (1 - shaper) * ((endX - initPosX) / 2.f) ); x+=1.f) {
			*pixel++ = color;
		}
		if( y < ( initPosY + static_cast<int>( (endY - initPosY) / 2.f ) ) )
			shaper += shaper_step;
		else
			shaper -= shaper_step;
	}
}

static void draw_side_lines(void* source_memory, float initPosX, float initPosY, float line_w, float halfSizeX, float halfSizeY, const float& maxWidth, const float& maxHeight)
{
	initPosX *= maxHeight * render_scale;
	halfSizeX *= maxHeight * render_scale;
	initPosY *= maxHeight * render_scale;
	halfSizeY *= maxHeight * render_scale;
	line_w *= maxHeight * render_scale;

	initPosX += maxWidth / 2.f;
	initPosY += maxHeight / 2.f;

	float endX = initPosX + halfSizeX;
	float endY = initPosY + halfSizeY;

	initPosX -= halfSizeX;
	initPosY -= halfSizeY;

	initPosX = clamp(0, initPosX, maxWidth);
	endX = clamp(0, endX, maxWidth);
	initPosY = clamp(0, initPosY, maxHeight);
	endY = clamp(0, endY, maxHeight);

	for (int y{ static_cast<int>(initPosY) }; y < static_cast<int>(endY); y++) {
		u32* pixel = reinterpret_cast<u32*>(source_memory) + static_cast<int>(initPosX) + y * static_cast<int>(maxWidth);
		for (int x{ static_cast<int>(initPosX) }; x < endX; x++) {
			if (
				((y > (initPosY + 3*line_w)) && (y < (endY - 4.5*line_w)))
				&&
				((x > (initPosX + 3*line_w)) && (x < (endX - 4*line_w)))
				)
			{
				pixel++;
				continue;
			}
			*pixel++ = side_lines.color;
		}
	}
}

static void draw_field(Render_State& state)
{
	//draw arena
	draw_rectangle(
		state.memory,
		arena.initial_position_x, arena.initial_position_y, arena.half_size_x, arena.half_size_y,
		static_cast<float>(state.width), static_cast<float>(state.height),
		arena.color
	);

	//draw center line
	draw_rectangle(
		state.memory,
		center_line.initial_position_x, center_line.initial_position_y, center_line.half_size_x, center_line.half_size_y,
		static_cast<float>(state.width), static_cast<float>(state.height),
		center_line.color
	);

	//draw side lines
	draw_side_lines(
		state.memory,
		side_lines.initial_position_x, side_lines.initial_position_y,
		side_lines.line_width,
		side_lines.half_size_x, side_lines.half_size_y,
		static_cast<float>(state.width), static_cast<float>(state.height)
	);

	//Draw LEFT gate
	draw_rectangle(
		state.memory,
		-arena.half_size_x-3.25f*std_half_width-gate_half_sizeX, gate.initial_position_y, gate.half_size_x, gate.half_size_y,
		static_cast<float>(state.width), static_cast<float>(state.height),
		gate.color
	);

	//Draw RIGHT gate
	draw_rectangle(
		state.memory,
		arena.half_size_x + 3.25f * std_half_width + gate_half_sizeX, gate.initial_position_y, gate.half_size_x, gate.half_size_y,
		static_cast<float>(state.width), static_cast<float>(state.height),
		gate.color
	);
}

static void draw_score(Render_State& state, const int& score, const int& side, const bool& two_digits = false)
{
	float exc{};
	if ( (side == 1) && two_digits ) exc = 1.5 * draw_offset + 5 * draw_offset;
	else if (side == 1) exc = 1.5 * draw_offset;
	else if ((side == -1) && two_digits) exc = - 1.5 * draw_offset;
	else if (side == -1) exc = - 1.5 * draw_offset + 5 * draw_offset;

	switch(score%10)
	{
		case 0:
		{
			for(int cube_x{}; cube_x < 4; cube_x++)
			{
				for (int cube_y{}; cube_y < 5; cube_y++)
				{
					if (
						((0 < cube_x) && (cube_x < 3))
						&&
						((0 < cube_y) && (cube_y < 4))
						) continue;
					else
					{
							draw_rectangle(reinterpret_cast<u32*>(state.memory),
								(side * (arena.half_size_x - 4.f - exc) + draw_offset * cube_x), (arena.half_size_y + 2.f + draw_offset * cube_y),
								cube_s, cube_s, static_cast<const float>(state.width), static_cast<const float>(state.height), 0xffffff);
					}
				}
			}
		} break;
		case 1:
		{
			int cube_x{3};
			for (int cube_y{}; cube_y < 5; cube_y++)
			{
				draw_rectangle(reinterpret_cast<u32*>(state.memory),
					(side * (arena.half_size_x - 4.f - exc) + draw_offset * cube_x), (arena.half_size_y + 2.f + draw_offset * cube_y),
					cube_s, cube_s, static_cast<const float>(state.width), static_cast<const float>(state.height), 0xffffff);
			}
		} break;
		case 2:
		{
			for (int cube_x{}; cube_x < 4; cube_x++)
			{
				for (int cube_y{}; cube_y < 5; cube_y++)
				{
					if (
						(((cube_x == 1) || (cube_x == 2)) && (cube_y == 3))
						||
						(((cube_x == 0) || (cube_x == 1) || (cube_x == 3)) && (cube_y == 2))
						||
						(((cube_x == 0) || (cube_x == 2) || (cube_x == 3)) && (cube_y == 1))
						) continue;
					else
					{
						draw_rectangle(reinterpret_cast<u32*>(state.memory),
							(side * (arena.half_size_x - 4.f - exc) + draw_offset * cube_x), (arena.half_size_y + 2.f + draw_offset * cube_y),
							cube_s, cube_s, static_cast<const float>(state.width), static_cast<const float>(state.height), 0xffffff);
					}
				}
			}
		} break;
		case 3:
		{
			for (int cube_x{}; cube_x < 4; cube_x++)
			{
				for (int cube_y{}; cube_y < 5; cube_y++)
				{
					if (
						(((cube_x == 0) || (cube_x == 1) || (cube_x == 2)) && (cube_y == 3))
						||
						(((cube_x == 0) || (cube_x == 1) || (cube_x == 2)) && (cube_y == 1))
						) continue;
					else
					{
						draw_rectangle(reinterpret_cast<u32*>(state.memory),
							(side * (arena.half_size_x - 4.f - exc) + draw_offset * cube_x), (arena.half_size_y + 2.f + draw_offset * cube_y),
							cube_s, cube_s, static_cast<const float>(state.width), static_cast<const float>(state.height), 0xffffff);
					}
				}
			}
		} break;
		case 4:
		{
			for (int cube_x{}; cube_x < 4; cube_x++)
			{
				for (int cube_y{}; cube_y < 5; cube_y++)
				{
					if (
						(((cube_x == 1) || (cube_x == 2)) && (cube_y == 4))
						||
						(((cube_x == 1) || (cube_x == 2)) && (cube_y == 3))
						||
						(((cube_x == 0) || (cube_x == 1) || (cube_x == 2)) && (cube_y == 1))
						||
						(((cube_x == 0) || (cube_x == 1) || (cube_x == 2)) && (cube_y == 0))
						) continue;
					else
					{
						draw_rectangle(reinterpret_cast<u32*>(state.memory),
							(side * (arena.half_size_x - 4.f - exc) + draw_offset * cube_x), (arena.half_size_y + 2.f + draw_offset * cube_y),
							cube_s, cube_s, static_cast<const float>(state.width), static_cast<const float>(state.height), 0xffffff);
					}
				}
			}
		} break;
		case 5:
		{
			for (int cube_x{}; cube_x < 4; cube_x++)
			{
				for (int cube_y{}; cube_y < 5; cube_y++)
				{
					if (
						(((cube_x == 1) || (cube_x == 2) || (cube_x == 3)) && (cube_y == 3))
						||
						(((cube_x == 0) || (cube_x == 1) || (cube_x == 2)) && (cube_y == 1))
						) continue;
					else
					{
						draw_rectangle(reinterpret_cast<u32*>(state.memory),
							(side * (arena.half_size_x - 4.f - exc) + draw_offset * cube_x), (arena.half_size_y + 2.f + draw_offset * cube_y),
							cube_s, cube_s, static_cast<const float>(state.width), static_cast<const float>(state.height), 0xffffff);
					}
				}
			}
		} break;
		case 6:
		{
			for (int cube_x{}; cube_x < 4; cube_x++)
			{
				for (int cube_y{}; cube_y < 5; cube_y++)
				{
					if (
						(((cube_x == 1) || (cube_x == 2) || (cube_x == 3)) && (cube_y == 3))
						||
						(((cube_x == 1) || (cube_x == 2)) && (cube_y == 1))
						) continue;
					else
					{
						draw_rectangle(reinterpret_cast<u32*>(state.memory),
							(side * (arena.half_size_x - 4.f - exc) + draw_offset * cube_x), (arena.half_size_y + 2.f + draw_offset * cube_y),
							cube_s, cube_s, static_cast<const float>(state.width), static_cast<const float>(state.height), 0xffffff);
					}
				}
			}
		} break;
		case 7:
		{
			for (int cube_x{}; cube_x < 4; cube_x++)
			{
				for (int cube_y{}; cube_y < 5; cube_y++)
				{
					if (
						(((cube_x == 0) || (cube_x == 1) || (cube_x == 2)) && (cube_y == 3))
						||
						(((cube_x == 0) || (cube_x == 1) || (cube_x == 2)) && (cube_y == 2))
						||
						(((cube_x == 0) || (cube_x == 1) || (cube_x == 2)) && (cube_y == 1))
						||
						(((cube_x == 0) || (cube_x == 1) || (cube_x == 2)) && (cube_y == 0))
						) continue;
					else
					{
						draw_rectangle(reinterpret_cast<u32*>(state.memory),
							(side * (arena.half_size_x - 4.f - exc) + draw_offset * cube_x), (arena.half_size_y + 2.f + draw_offset * cube_y),
							cube_s, cube_s, static_cast<const float>(state.width), static_cast<const float>(state.height), 0xffffff);
					}
				}
			}
		} break;
		case 8:
		{
			for (int cube_x{}; cube_x < 4; cube_x++)
			{
				for (int cube_y{}; cube_y < 5; cube_y++)
				{
					if (
						(((cube_x == 1) || (cube_x == 2)) && (cube_y == 3))
						||
						(((cube_x == 1) || (cube_x == 2)) && (cube_y == 1))
						) continue;
					else
					{
						draw_rectangle(reinterpret_cast<u32*>(state.memory),
							(side * (arena.half_size_x - 4.f - exc) + draw_offset * cube_x), (arena.half_size_y + 2.f + draw_offset * cube_y),
							cube_s, cube_s, static_cast<const float>(state.width), static_cast<const float>(state.height), 0xffffff);
					}
				}
			}
		} break;
		case 9:
		{
			for (int cube_x{}; cube_x < 4; cube_x++)
			{
				for (int cube_y{}; cube_y < 5; cube_y++)
				{
					if (
						(((cube_x == 1) || (cube_x == 2)) && (cube_y == 3))
						||
						(((cube_x == 0) || (cube_x == 1) || (cube_x == 2)) && (cube_y == 1))
						) continue;
					else
					{
						draw_rectangle(reinterpret_cast<u32*>(state.memory),
							(side * (arena.half_size_x - 4.f - exc) + draw_offset * cube_x), (arena.half_size_y + 2.f + draw_offset * cube_y),
							cube_s, cube_s, static_cast<const float>(state.width), static_cast<const float>(state.height), 0xffffff);
					}
				}
			}
		} break;

	}
}