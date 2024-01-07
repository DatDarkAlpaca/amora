#pragma once
#include <vector>
#include <memory>
#include <numeric>

#include "scene.hpp"

namespace amo
{
	class SceneHolder
	{
	public:
		inline uint32_t add_scene(std::unique_ptr<IScene> scene)
		{
			scene->initialize();
			m_Scenes.push_back(std::move(scene));

			return m_Scenes.size() - 1;
		}

		inline const std::unique_ptr<IScene>& get_scene(uint32_t index) const
		{
			return m_Scenes[index];
		}

	public:
		std::vector<std::unique_ptr<IScene>>::iterator begin() { return m_Scenes.begin(); }

		std::vector<std::unique_ptr<IScene>>::iterator end() { return m_Scenes.end(); }

	private:
		std::vector<std::unique_ptr<IScene>> m_Scenes;
	};
}