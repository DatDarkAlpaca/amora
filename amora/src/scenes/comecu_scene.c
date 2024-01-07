#include "comecu_scene.h"

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include <windows.h> // TODO: add header guards

#include "utils/file.h"
#include "utils/input.h"

static file_results frames[8];
static bool framesLoaded = false;

bool comecu_scene_initialize()
{
	clear_screen();

	if (framesLoaded)
		return;

	for (unsigned i = 0; i < 8; ++i)
	{
		size_t length = snprintf(NULL, 0, "%d", (int)i + 1);
		char* str = malloc(length + 1);
		if(!str)
		{
			printf("Failed to load pig arts.\n\n");
			return false;
		}

		snprintf(str, length + 1, "%d", (int)i + 1);

		char* filepath = (char*)calloc(32, sizeof(char));
		if (!filepath)
		{
			printf("Failed to load pig arts.\n\n");
			return false;
		}

		strcat(filepath, "res/pig/pig");
		strcat(filepath, str);
		strcat(filepath, ".txt");

		free(str);

		frames[i] = read_file(filepath);
		if (!frames[i].valid)
		{
			printf("Failed to load pig arts.\n\n");
			return false;
		}

		free(filepath);
	}

	framesLoaded = true;
}

bool comecu_scene_display()
{
	unsigned int currentIndex = 0;
	while (true)
	{
		clear_screen();
		printf("%s\n\n", frames[currentIndex].contents);
		currentIndex++;
		currentIndex %= 8;

		Sleep(100);
	}
}

void comecu_scene_handle_command(int command)
{
}

bool comecu_scene_update()
{
	return true;
}
