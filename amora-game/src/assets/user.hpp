#pragma once
#include <numeric>
#include <string>

#include "physics/rigid_body.hpp"
#include "utils/random.hpp"

namespace amo
{
	struct User
	{
	public:
		explicit User()
		{
			maxArmor = amo::Random::get(MaxArmorLower, MaxArmorUpper);
			maxLife = amo::Random::get(MaxLifeLower, MaxLifeUpper);

			currentArmor = maxArmor;
			currentLife = maxLife;
		}
	
	public:
		std::string name = "Guts";
		uint32_t maxLife = 0, currentLife = 0;
		uint32_t maxArmor = 0, currentArmor = 0;

	public:
		Rigidbody rigidbody;

	public:
		constexpr static inline uint32_t MaxLifeLower = 10;
		constexpr static inline uint32_t MaxLifeUpper = 20;

		constexpr static inline uint32_t MaxArmorLower = 10;
		constexpr static inline uint32_t MaxArmorUpper = 20;
	};
}