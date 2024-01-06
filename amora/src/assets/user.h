#pragma once
#include "weapon.h"

typedef struct user
{
	char userName[32];

	unsigned int maxLife;
	unsigned int currentLife;
	
	unsigned int maxArmor;
	unsigned int currentArmor;

	weapon carryWeapon;
} user;

void create_user();

void display_user_stats();