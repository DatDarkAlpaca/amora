#include "entity.hpp"

namespace amo
{
	Entity::Entity(entt::entity entity, Scene* scene)
		: m_Entity(entity)
		, m_Scene(scene)
	{

	}
}
