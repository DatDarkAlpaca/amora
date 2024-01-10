#pragma once
#include <entt/entt.hpp>
#include "utils/uuid.hpp"

namespace amo
{
	class Entity;

	class Scene
	{
		friend class Entity;

	public:
		Entity create_entity();

		void remove_entity(Entity entity);

	public:
		std::unordered_map<UUID, Entity> m_EntityLookup;
		entt::registry m_Registry;
	};
}