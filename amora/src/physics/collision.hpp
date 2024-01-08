#pragma once
#include "utils/vec2.hpp"
#include "rigid_body.hpp"

namespace amo
{
	inline bool aabb_detection(const Rigidbody& lhs, const Rigidbody& rhs)

	{
		return (uint32_t)lhs.position.x == (uint32_t)rhs.position.x && 
			   (uint32_t)lhs.position.y == (uint32_t)rhs.position.y;
	}

	inline bool aabb_detection(const Rigidbody& lhs, const vec2u& rhs)

	{
		return (uint32_t)lhs.position.x == (uint32_t)rhs.x &&
			(uint32_t)lhs.position.y == (uint32_t)rhs.y;
	}

	inline void collision_resolution(Rigidbody& lhs, Rigidbody& rhs)
	{
		if (!lhs.isStatic)
		{
			if(lhs.velocity.x != 0)
				lhs.position.x -= lhs.velocity.x > 0 ? 1 : -1;
			
			if (lhs.velocity.y != 0)
				lhs.position.y -= lhs.velocity.y > 0 ? 1 : -1;
		}
		if (!rhs.isStatic)
		{
			rhs.velocity.x = -rhs.velocity.x;
			rhs.velocity.y = -rhs.velocity.y;
		}
	}
}