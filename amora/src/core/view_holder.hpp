#pragma once
#include <vector>
#include <memory>
#include <numeric>

#include "common.hpp"
#include "view.hpp"

namespace amo
{
	// Note: Overlays are always executed, as opposed to scenes. Only the active scene gets executed.

	class ViewHolder
	{
	public:
		uint32_t add_view(std::unique_ptr<IView> scene);

		uint32_t add_overlay(std::unique_ptr<IView> scene);

		const std::unique_ptr<IView>& get_scene(uint32_t index) const;

		const std::unique_ptr<IView>& get_overlay(uint32_t index) const;

	public:
		const std::vector<std::unique_ptr<IView>>& scenes() const { return m_Scenes; }

		const std::vector<std::unique_ptr<IView>>& overlays() const { return m_Overlays; }

		std::vector<std::unique_ptr<IView>>& scenes() { return m_Scenes; }

		std::vector<std::unique_ptr<IView>>& overlays() { return m_Overlays; }

	public:
		inline NON_OWNING IView* current() const { return m_CurrentScene; }

		void set_current(uint32_t index);

	private:
		std::vector<std::unique_ptr<IView>> m_Scenes;
		std::vector<std::unique_ptr<IView>> m_Overlays;
		NON_OWNING IView* m_CurrentScene = nullptr;
	};
}