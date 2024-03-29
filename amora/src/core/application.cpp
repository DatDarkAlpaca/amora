#include "application.hpp"

namespace amo
{
	Application::Application(const std::string& title, uint32_t width, uint32_t height)
		: m_Console(title, width, height)
	{
		m_Console.set_event_callback(std::bind(&Application::handle_event, this, std::placeholders::_1));
		m_Running = true;
	}

	uint32_t Application::add_view(std::unique_ptr<IView> scene)
	{
		return m_SceneHolder.add_view(std::move(scene));
	}

	uint32_t Application::add_overlay(std::unique_ptr<IView> overlay)
	{
		return m_SceneHolder.add_overlay(std::move(overlay));
	}

	void Application::set_scene(uint32_t sceneIndex)
	{
		m_SceneHolder.set_current(sceneIndex);
	}

	void Application::update(double dt)
	{
		if (!m_SceneHolder.current())
			return;

		m_SceneHolder.current()->update(dt);

		for (const auto& overlay : m_SceneHolder.overlays())
			overlay->update(dt);
	}

	void Application::render()
	{
		if (!m_SceneHolder.current())
			return;

		m_SceneHolder.current()->render(&m_Console);

		for (const auto& overlay : m_SceneHolder.overlays())
			overlay->render(&m_Console);
	}

	void Application::handle_event(const INPUT_RECORD& inputRecord)
	{
		if (!m_SceneHolder.current())
			return;

		m_SceneHolder.current()->handle_event(inputRecord);

		for (const auto& overlay : m_SceneHolder.overlays())
			overlay->handle_event(inputRecord);
	}

	void Application::set_display_rate(double drawRate, double updateRate)
	{
		m_DrawRate = drawRate;
		m_UpdateRate = updateRate;
	}

	void Application::run()
	{
		using namespace std::chrono;

		while (m_Running)
		{
			high_resolution_clock::time_point now = high_resolution_clock::now();
			duration<double> updateSpan = duration_cast<duration<double>>(now - m_LastUpdate);
			duration<double> drawSpan = duration_cast<duration<double>>(now - m_LastDraw);

			m_Console.poll_events();
			
			if (updateSpan.count() >= m_UpdateRate / 1000.0)
			{
				m_LastUpdate = now;
				update(updateSpan.count());
			}

			if (drawSpan.count() >= m_DrawRate / 1000.0)
			{
				m_LastDraw = now;
				m_Console.clear();

				render();
				
				m_Console.display();
			}
		}
	}
}