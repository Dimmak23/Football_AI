#pragma once

#include "utilities.h"
#include "typenames.h"

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

static void clear_screen(u32* source_memory, const int& h, const int& w, const u32& color) {
	
	for (int screen_px{}; screen_px < h*w; screen_px++) {
			*source_memory++ = color;
	}
}

static void draw_normal_triangle(void* source_memory, float initPosX, float initPosY, float& halfSizeX, float& halfSizeY, const float& maxWidth, const float& maxHeight, const u32& color) {

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


static void draw_rectangle(void* source_memory, float initPosX, float initPosY, float halfSizeX, float halfSizeY, const float& maxWidth, const float& maxHeight, const u32& color) {

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