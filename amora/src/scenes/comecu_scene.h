#pragma once
#include <stdbool.h>

bool comecu_scene_initialize();
	 
bool comecu_scene_display();
	 
void comecu_scene_handle_command(int command);
	 
bool comecu_scene_update();