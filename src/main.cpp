/**
 * Copyright 2015 Your Name <you@yourhost.com>
 *
 * @brief Description of My Awesome Game.
 *
 * @file main.cpp
 *
 * @mainpage My Awesome Game
 *
 * @section intro Introduction
 *
 * Detailed description of My Awesome Game.
 *
 * There's even a second paragraph.
 */
#include <rt2d/core.h>

#include "scenemanager.h"

/// @brief main entry point
int main(void)
{
	// Core instance
	Core core;

	// Scene01
	SceneManager *scenemanager = new SceneManager(); // create Scene on the heap
	while (scenemanager->isRunning())
	{													// check status of Scene every frame
		core.run(scenemanager); // update and render the current scene
		core.showFrameRate(2);	// show framerate in output every n seconds
	}
	// core.cleanup(); // cleanup ResourceManager (Textures + Meshes, but not Shaders)
	delete scenemanager; // delete Scene and everything in it from the heap to make space for next Scene

	// No need to explicitly clean up the core.
	// As a local var, core will go out of scope and destroy Renderer->ResourceManager.
	// ResourceManager destructor also deletes Shaders.

	return 0;
}
