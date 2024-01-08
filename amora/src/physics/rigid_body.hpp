#pragma once
#include "utils/vec2.hpp"

namespace amo
{
	struct Rigidbody
	{
	public:
		vec2f position = { 0.f, 0.f }, velocity = { 0.f, 0.f };
		bool isStatic = false;
	};
}