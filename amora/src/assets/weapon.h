#pragma once

typedef struct weapon
{
	const char* name;
	unsigned int damage;
} weapon;

void initialize_weapons();

weapon choose_random_weapon();