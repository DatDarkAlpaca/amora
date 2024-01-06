#pragma once
#include <stdbool.h>

bool play_scene_initialize();

bool play_scene_display();

void play_scene_handle_command(char* command);

bool play_scene_update();