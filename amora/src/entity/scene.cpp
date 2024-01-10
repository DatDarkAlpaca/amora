#include "scene.hpp"
#include "entity.hpp"

#include "components.hpp"

namespace amo
{
	Entity Scene::create_entity()
	{
		Entity entity(m_Registry.create(), this);
		auto& uuid = entity.add_component<UUIDComponent>();

		m_EntityLookup[uuid.uuid] = entity;
		return entity;
	}

	void Scene::remove_entity(Entity entity)
	{
		m_EntityLookup.erase(entity.uuid());
		m_Registry.destroy(entity);
	}
}