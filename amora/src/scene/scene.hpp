#pragma once
#include "constants.hpp"
#include "windows_header.hpp"

namespace amo
{
	class AmoraConsole;
	class SceneHolder;

	class IScene
	{
	public:
		virtual ~IScene() = default;

	public:
		virtual void initialize() { }

		virtual void update(double dt) { }

		virtual void render(AmoraConsole*) { }

		virtual void handle_event(const INPUT_RECORD&) { }

	public:
		inline void set_scene_holder(SceneHolder* holder) { this->holder = holder; }

	protected:
		NON_OWNING SceneHolder* holder = nullptr;
	};
}