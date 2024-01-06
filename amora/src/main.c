#include <stdbool.h>
#include <stdlib.h>
#include <locale.h>

#include "common.h"
#include "state.h"
#include "assets/weapon.h"

static void initialize()
{
	srand((unsigned int)time(NULL));

	initialize_weapons();

	initialize_scenes();

	_state.running = true;
}

static bool run()
{
	if (!_state.currentScene->display())
		return false;

	if (!_state.currentScene->update())
		return false;

	return true;
}

int main()
{
	initialize();

	while (_state.running)
	{
		if (!run())
			return 1;
	}

	return RESULT_OK;
}