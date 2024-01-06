#include "weapon.h"
#include "state.h"

#include <stdlib.h>
#include <time.h>

void initialize_weapons()
{
	_state.availableWeaponCount = 3;

	_state.availableWeapons[0].name = "katana";
	_state.availableWeapons[0].damage = 1;

	_state.availableWeapons[1].name = "longsword";
	_state.availableWeapons[1].damage = 2;

	_state.availableWeapons[2].name = "scimitar";
	_state.availableWeapons[2].damage = 3;
}

weapon choose_random_weapon()
{
	int randomWeaponIndex = rand() % (_state.availableWeaponCount);
	return _state.availableWeapons[randomWeaponIndex];
}
