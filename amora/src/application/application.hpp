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
		void update(double dt);

		void render();

		void handle_event(INPUT_RECORD inputRecord);

	public:
		void set_display_rate(double drawRate, double updateRate);

	private:
		AmoraConsole m_Console;
		SceneHolder m_SceneHolder;

	private:
		std::chrono::high_resolution_clock::time_point m_LastUpdate, m_LastDraw;
		double m_DrawRate = 1000 / 25, m_UpdateRate = 0;

		bool m_Running = false;
	};
}