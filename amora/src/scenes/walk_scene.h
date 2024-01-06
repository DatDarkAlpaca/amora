#pragma once
#include <stdbool.h>

bool walk_scene_initialize();

bool walk_scene_display();

void walk_scene_handle_command(char* command);

bool walk_scene_update();