#pragma once
#include "utils/vec2.hpp"

namespace amo
{
	struct Rigidbody
	{
	public:
		vec2f position = { 0.f, 0.f }, velocity = { 0.f, 0.f };
		float speed = 16.5f;
		bool isStatic = false;
	};
}