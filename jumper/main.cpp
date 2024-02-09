/**
 * Copyright 2024 D. Westerdijk <you@yourhost.com>
 *
 * @brief RT2D initialisation of Jumper
 *
 * @file main.cpp
 *
 * @mainpage Jumper is a clone of Geometry Dash made to practice C++, OOP concepts and RT2D
 *
 * @section Introduction
 *
 * Jumper is a 2D sidescroller-platformer where you jump over spikes and on
 * squares.
 * Dodge spikes by jumping over them and be careful not to hit your head against
 * the squares!
 */
#include <rt2d/core.h>

#include "jumper.h"

/// @brief main entry point
int main(void)
{
	// Core instance
	Core core;

	// Scene01
	Jumper *jumper01 = new Jumper(); // create Scene on the heap
	while (jumper01->isRunning())
	{												 // check status of Scene every frame
		core.run(jumper01);		 // update and render the current scene
		core.showFrameRate(1); // show framerate in output every n seconds
	}
	// core.cleanup(); // cleanup ResourceManager (Textures + Meshes, but not Shaders)
	delete jumper01; // delete Scene and everything in it from the heap to make space for next Scene

	// No need to explicitly clean up the core.
	// As a local var, core will go out of scope and destroy Renderer->ResourceManager.
	// ResourceManager destructor also deletes Shaders.

	return 0;
}
