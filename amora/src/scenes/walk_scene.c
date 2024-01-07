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
	return true;
}

void walk_scene_handle_command(char* _command)
{
	/* Blank */
}

bool walk_scene_update()
{
	printf("You walk amidst the valley...\n\n");

	wait_press();

	transition_scene(3);

	// swap_scene(1);

	return true;
}
