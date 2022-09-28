#pragma once

#include "utilities.h"
#include "typenames.h"

static void clear_screen(u32* source_memory, const int& h, const int& w, const u32& color) {
	
	for (int screen_px{}; screen_px < h*w; screen_px++) {
			*source_memory++ = color;
	}
}

static void draw_rectangle_in_pixels(void* source_memory, int&& initPosX, int&& initPosY, int&& endX, int&& endY, const int& maxWidth, const int& maxHeight, const u32& color) {

	//We need to privent going outside of the allocated memory by 'pixel'
	//when moving game window
	/*
	Clamps the specified value to the specified minimum and maximum range
	<return_value> clamp(min, x, max)
	The clamped value for the x parameter.
	*/
	initPosX = clamp(0, initPosX, maxWidth);
	endX = clamp(0, endX, maxWidth);
	initPosY = clamp(0, initPosY, maxHeight);
	endY = clamp(0, endY, maxHeight);

	for (int y{ initPosY }; y < endY; y++) {
		u32* pixel = reinterpret_cast<u32*>(source_memory) + initPosX + y*maxWidth;
		for (int x{ initPosX }; x < endX; x++) {
			*pixel++ = color;
		}
	}
}

static void draw_rectangle(void* source_memory, float&& initPosX, float&& initPosY, float&& halfSizeX, float&& halfSizeY, const int& maxWidth, const int& maxHeight, const u32& color) {
	//Change to pixels
	//Everything multiplied by maxHeight - size of the screen -> when we move width size - nothing change,
	//when we move height size - game window updates
	initPosX *= maxHeight * render_scale;
	halfSizeX *= maxHeight * render_scale;
	initPosY *= maxHeight * render_scale;
	halfSizeY *= maxHeight * render_scale;

	//Let's upply logic to center sprite:
	initPosX += maxWidth / 2.f;
	initPosY += maxHeight / 2.f;

	//Then we sent them to the center of the screen
	draw_rectangle_in_pixels(source_memory, initPosX - halfSizeX, initPosY - halfSizeY, initPosX + halfSizeX, initPosY + halfSizeY, maxWidth, maxHeight, color);
}