#pragma once
#include <stdbool.h>

#include "assets/weapon.h"
#include "assets/user.h"
#include "assets/scene.h"

typedef struct state
{
	bool running;

	// Scenes:
	unsigned sceneCount;
	scene scenes[8];
	scene* currentScene;

	// Assets:
	unsigned availableWeaponCount;
	weapon availableWeapons[8];

	user player;
} state;

state _state;