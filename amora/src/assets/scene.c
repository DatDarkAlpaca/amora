#include "scene.h"
#include "state.h"

#include "scenes/main_scene.h"
#include "scenes/play_scene.h"
#include "scenes/walk_scene.h"
#include "scenes/comecu_scene.h"

void initialize_scenes()
{
	_state.sceneCount = 2;
	_state.currentScene = &_state.scenes[0];

	_state.scenes[0].initialize = main_scene_initialize;
	_state.scenes[0].display = main_scene_display;
	_state.scenes[0].update = main_scene_update;

	_state.scenes[1].initialize = play_scene_initialize;
	_state.scenes[1].display = play_scene_display;
	_state.scenes[1].update = play_scene_update;

	_state.scenes[2].initialize = walk_scene_initialize;
	_state.scenes[2].display = walk_scene_display;
	_state.scenes[2].update = walk_scene_update;

	_state.scenes[3].initialize = comecu_scene_initialize;
	_state.scenes[3].display = comecu_scene_display;
	_state.scenes[3].update = comecu_scene_update;

	transition_scene(1);
}

void transition_scene(unsigned int sceneIndex)
{
	_state.currentScene = &_state.scenes[sceneIndex];
	_state.currentScene->initialize();
}

void swap_scene(unsigned int sceneIndex)
{
	_state.currentScene = &_state.scenes[sceneIndex];
}
