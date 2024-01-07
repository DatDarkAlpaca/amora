#pragma once
#include <chrono>

#include "console/console.hpp"
#include "scene/scene_holder.hpp"

namespace amo
{
	class Application
	{
	public:
		explicit Application(const std::string& title, uint32_t width, uint32_t height);

	public:
		void run();

	public:
		uint32_t add_scene(std::unique_ptr<IScene> scene);

	public:
		void update();

		void render();

		void handle_event(INPUT_RECORD inputRecord);

	private:
		AmoraConsole m_Console;
		SceneHolder m_SceneHolder;

	private:
		bool m_Running = false;
	};
}