#pragma once
#include <glm/glm.hpp>
#include "windows_header.hpp"

#include "utils/direction.hpp"
#include "utils/uuid.hpp"

namespace amo
{
	struct UUIDComponent
	{
	public:
		UUIDComponent() = default;
		UUIDComponent(const UUIDComponent&) = default;

	public:
		operator UUID () { return uuid; }

	public:
		UUID uuid;
	};

	struct TransformComponent
	{
	public:
		TransformComponent() = default;
		TransformComponent(const TransformComponent&) = default;
		TransformComponent(const glm::vec2& position) : position(position) { }

	public:
		glm::vec2 position;
	};

	struct SpriteComponent
	{
	public:
		SpriteComponent() = default;
		SpriteComponent(const SpriteComponent&) = default;
		SpriteComponent(const CHAR_INFO& charInfo) : data(charInfo) { }

	public:
		CHAR_INFO data;
	};

	struct MovementComponent
	{
	public:
		MovementComponent() = default;
		MovementComponent(const MovementComponent&) = default;

	public:
		Direction direction;
	};

	struct RigidbodyComponent
	{
	public:
		RigidbodyComponent() = default;
		RigidbodyComponent(const RigidbodyComponent&) = default;

	public:
		glm::vec2 velocity = { 0.f, 0.f };
		float speed = 16.5f;
		bool isStatic = false;
	};
}