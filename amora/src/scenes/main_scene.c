#include "main_scene.h"
#include <stdio.h>

#include "common.h"
#include "state.h"
#include "utils/file.h"
#include "utils/input.h"

bool main_scene_initialize()
{
	clear_screen();
	return true;
}

bool main_scene_display()
{
	// Welcome Art:
	{
		file_results welcomeArt = read_file("res/welcome_art.txt");
		if (!welcomeArt.valid)
			return RESULT_FAILED;

		printf("%s\n\n\n", welcomeArt.contents);
		close_file(welcomeArt);
	}

	// Options:
	{
		printf("Type the corresponding number as an input command. The commands are shown below.\n\n");

		printf("\t[ 1 ] Start Game\n");
		printf("\t[ 2 ] Quit");

		printf("\n\n");
	}

	return RESULT_OK;
}

void main_scene_handle_command(int command)
{
	switch (command)
	{
		case 1:
		{
			transition_scene(1);
		} break;

		case 2:
		{
			printf("Good bye!");
			_state.running = false;
		} break;

		default:
			printf("Please enter a valid command.\n");
			break;
	}

	return true;
}

bool main_scene_update()
{
	int userInput = get_input_number();
	if (userInput == INVALID_NUMBER)
	{
		printf("Please insert a valid option. Press any key to continue...\n");
		flush();

		return true;
	}

	main_scene_handle_command(userInput);
	return true;
}
