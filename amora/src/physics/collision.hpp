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
			if (lhs.velocity.x != 0)
			{
				auto inverseX = lhs.velocity.x > 0 ? -1 : 1;
				lhs.position.x += inverseX;
			}
			
			if (lhs.velocity.y != 0)
			{
				auto inverseY = lhs.velocity.y > 0 ? -1 : 1;
				lhs.position.y += inverseY;
			}
		}

		if (!rhs.isStatic)
		{
			if (rhs.velocity.x != 0)
			{
				auto inverseX = rhs.velocity.x > 0 ? -1 : 1;
				rhs.position.x += inverseX;
			}

			if (rhs.velocity.y != 0)
			{
				auto inverseY = rhs.velocity.y > 0 ? -1 : 1;
				rhs.position.y += inverseY;
			}
		}
	}
}