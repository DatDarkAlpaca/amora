#pragma once
#include <vector>
#include <memory>
#include <numeric>

#include "common.hpp"
#include "scene.hpp"

namespace amo
{
	// Note: Overlays are always executed, as opposed to scenes. Only the active scene gets executed.

	class SceneHolder
	{
	public:
		uint32_t add_scene(std::unique_ptr<IScene> scene);

		uint32_t add_overlay(std::unique_ptr<IScene> scene);

		const std::unique_ptr<IScene>& get_scene(uint32_t index) const;

		const std::unique_ptr<IScene>& get_overlay(uint32_t index) const;

	public:
		const std::vector<std::unique_ptr<IScene>>& scenes() const { return m_Scenes; }

		const std::vector<std::unique_ptr<IScene>>& overlays() const { return m_Overlays; }

		std::vector<std::unique_ptr<IScene>>& scenes() { return m_Scenes; }

		std::vector<std::unique_ptr<IScene>>& overlays() { return m_Overlays; }

	public:
		inline NON_OWNING IScene* current() const { return m_CurrentScene; }

		void set_current(uint32_t index);

	private:
		std::vector<std::unique_ptr<IScene>> m_Scenes;
		std::vector<std::unique_ptr<IScene>> m_Overlays;
		NON_OWNING IScene* m_CurrentScene = nullptr;
	};
}