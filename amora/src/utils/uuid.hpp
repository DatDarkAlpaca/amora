#pragma once
#include <numeric>
#include "utils/random.hpp"

namespace amo
{
	class UUID
	{
	public:
		UUID()
			: m_UUID(Random<uint64_t>::get())
		{
		}

	public:
		operator uint64_t() const { return m_UUID; }

	private:
		uint64_t m_UUID;
	};
}

namespace std
{
	template<typename T>
	struct hash;

	template<>
	struct hash<amo::UUID>
	{
		uint64_t operator() (const amo::UUID& uuid) const
		{
			return static_cast<uint64_t>(uuid);
		}
	};
}