#pragma once
#include <numeric>
#include <random>

namespace amo
{
	class Random 
	{
	public:
		static uint32_t get(uint32_t lower, uint32_t upper)
		{
			std::uniform_int_distribution<uint32_t> distribution(lower, upper);
			return distribution(m_Generator);
		}

	private:
		static inline std::mt19937_64 m_Generator { std::random_device()() };
	};
}