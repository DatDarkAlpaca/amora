#include "scene_holder.hpp"

namespace amo
{
	uint32_t SceneHolder::add_scene(std::unique_ptr<IScene> scene)
	{
		scene->initialize();
		scene->set_scene_holder(this);

		m_Scenes.push_back(std::move(scene));
		m_CurrentScene = m_Scenes.back().get();

		return (uint32_t)m_Scenes.size() - 1;
	}

	uint32_t SceneHolder::add_overlay(std::unique_ptr<IScene> overlay)
	{
		overlay->initialize();
		overlay->set_scene_holder(this);

		m_Overlays.push_back(std::move(overlay));
		return (uint32_t)m_Overlays.size() - 1;
	}

	const std::unique_ptr<IScene>& SceneHolder::get_scene(uint32_t index) const
	{
		return m_Scenes[index];
	}

	const std::unique_ptr<IScene>& SceneHolder::get_overlay(uint32_t index) const
	{
		return m_Overlays[index];
	}

	void SceneHolder::set_current(uint32_t index) 
	{
		m_CurrentScene = m_Scenes[index].get();
	}
}