#pragma once
#include <entt/entt.hpp>

#include "common.hpp"
#include "scene.hpp"
#include "components.hpp"

namespace amo
{
	class Entity
	{
	public:
		explicit Entity(entt::entity entity, Scene* scene);
		
		explicit Entity() = default;

	public:
		template<typename T, typename... Args>
		T& add_component(Args&&... args)
		{
			T& component = m_Scene->m_Registry.emplace<T>(m_Entity, std::forward<Args>(args)...);
			return component;
		}

		template<typename T>
		T& get_component() const
		{
			return m_Scene->m_Registry.get<T>(m_Entity);
		}

		template<typename T>
		bool has_component() const
		{
			return m_Scene->m_Registry.all_of<T>(m_Entity);
		}

	public:
		operator entt::entity() { return m_Entity; }

	public:
		UUID uuid() const
		{ 
			return get_component<UUIDComponent>();
		}

	private:
		entt::entity m_Entity = entt::null;
		NON_OWNING Scene* m_Scene = nullptr;
	};
}