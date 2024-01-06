#include "play_scene.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "common.h"
#include "state.h"

#include "utils/file.h"
#include "utils/input.h"

bool play_scene_initialize()
{
	clear_screen();
	create_user();
	
	return true;
}

bool play_scene_display()
{
	clear_screen();

	// Arena Text:
	{
		file_results welcomeArt = read_file("res/arena.txt");
		if (!welcomeArt.valid)
			return RESULT_FAILED;

		printf("%s\n\n\n", welcomeArt.contents);
		close_file(welcomeArt);
	}

	// Player Status:
	display_user_stats();

	// Options:
	{
		printf("Available commands:\n");
		printf("* name\n");
		printf("* walk\n");
		printf("* exit\n");
	}

	return RESULT_OK;
}

void play_scene_handle_command(char* command)
{
	if (strncmp(command, "name", 4) == 0)
	{
		strcpy(_state.player.userName, command + 5);

		printf("%s\n", _state.player.userName);
		printf("Your name is now: %s", _state.player.userName);
	}

	else if (strncmp(command, "die", 3) == 0)
	{
		clear_screen();

		// Death Art:
		{
			file_results kysArt = read_file("res/kys.txt");
			if (!kysArt.valid)
				return;

			printf("%s\n\n", kysArt.contents);
			close_file(kysArt);
		}

		printf("You have disonored your breathen. May your soul never find peace...\n\n");
		wait_press();
		_state.running = false;
	}

	else if (strncmp(command, "walk", 4) == 0)
		swap_scene(2);

	else if (strncmp(command, "exit", 4) == 0)
		_state.running = false;
}

bool play_scene_update()
{
	char* userInput = get_input();

	play_scene_handle_command(userInput);

	return true;
}
