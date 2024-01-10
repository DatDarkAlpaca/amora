#pragma once
#include <chrono>

#include "core/view_holder.hpp"
#include "core/console.hpp"

namespace amo
{
	class Application
	{
	public:
		explicit Application(const std::string& title, uint32_t width, uint32_t height);

	public:
		void run();

	public:
		uint32_t add_view(std::unique_ptr<IView> scene);

		uint32_t add_overlay(std::unique_ptr<IView> overlay);

		void set_scene(uint32_t sceneIndex);

	public:
		void update(double dt);

		void render();

		void handle_event(const INPUT_RECORD& inputRecord);

	public:
		void set_display_rate(double drawRate, double updateRate);

	private:
		ViewHolder m_SceneHolder;
		AmoraConsole m_Console;

	private:
		std::chrono::high_resolution_clock::time_point m_LastUpdate, m_LastDraw;
		double m_DrawRate = 1000 / 24, m_UpdateRate = 0;

	private:
		bool m_Running = false;
	};
}