#include <stdio.h>

#include "walk_scene.h"

#include "assets/event.h"
#include "assets/scene.h"
#include "utils/input.h"

static event currentEvent;

bool walk_scene_initialize()
{
	clear_screen();
	currentEvent = generate_random_event();

	return true;
}

bool walk_scene_display()
{
	printf("You have walk far from your previous location.\n\n");

	// TODO: implement walk events

	return true;
}

void walk_scene_handle_command(char* _command)
{
	/* Blank */
}

bool walk_scene_update()
{
	wait_press();

	swap_scene(1);

	return true;
}
