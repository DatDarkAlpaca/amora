#include "application.hpp"

namespace amo
{
	Application::Application(const std::string& title, uint32_t width, uint32_t height)
		: m_Console(title, width, height)
	{
		m_Console.set_event_callback(std::bind(&Application::handle_event, this, std::placeholders::_1));

		m_Running = true;
	}

	uint32_t Application::add_scene(std::unique_ptr<IScene> scene)
	{
		return m_SceneHolder.add_scene(std::move(scene));
	}

	void Application::update()
	{
		for (const auto& scene : m_SceneHolder)
			scene->update();
	}

	void Application::render()
	{
		for (const auto& scene : m_SceneHolder)
			scene->render(&m_Console);			
	}

	void Application::handle_event(INPUT_RECORD inputRecord)
	{
		for (const auto& scene : m_SceneHolder)
			scene->handle_event(inputRecord);
	}

	void Application::run()
	{
		while (m_Running)
		{
			m_Console.poll_events();

			update();

			render();
		}
	}
}