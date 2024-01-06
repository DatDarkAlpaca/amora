#pragma once
#include <stdbool.h>

typedef struct scene
{
	bool (*initialize)();

	bool (*display)();

	bool (*update)();
} scene;

void initialize_scenes();

void transition_scene(unsigned int sceneIndex);

void swap_scene(unsigned int sceneIndex);