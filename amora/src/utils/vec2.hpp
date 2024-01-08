#pragma once
#include <numeric>

namespace amo
{
	template<typename T>
	struct vec2
	{
		T x, y;
	};

	using vec2u = vec2<uint32_t>;
	using vec2f = vec2<float>;
}