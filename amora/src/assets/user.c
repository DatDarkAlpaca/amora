#include <string.h>

#include "utils/random.h"
#include "constants.h"
#include "user.h"
#include "state.h"

void create_user()
{
	strcpy(_state.player.userName, "Guts");
	_state.player.carryWeapon = choose_random_weapon();

	_state.player.maxLife = get_rand_int(MAX_LIFE_LOWER, MAX_LIFE_UPPER);
	_state.player.currentLife = _state.player.maxLife;

	_state.player.maxArmor = get_rand_int(MAX_ARMOR_LOWER, MAX_ARMOR_UPPER);
	_state.player.currentArmor = _state.player.maxArmor;
}

void display_user_stats()
{
	printf("%s, embrace for impact!\n", _state.player.userName);

	printf("HP: %d/%d\n", _state.player.currentLife, _state.player.maxLife);
	printf("AR: %d/%d\n", _state.player.currentArmor, _state.player.maxArmor);

	printf("\n");

	printf(" * You are wielding a %s. It does %dx damage\n",
		_state.player.carryWeapon.name,
		_state.player.carryWeapon.damage
	);

	printf("\n\n");
}
