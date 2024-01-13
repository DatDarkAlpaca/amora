#pragma once
#include <amora.hpp>

#include "arena_scene.hpp"
#include "windows_header.hpp"

namespace amo
{
    void ArenaScene::initialize()
    {
        initialize_weapon();

        // User:
        {
            CHAR_INFO playerSprite;
            playerSprite.Char.AsciiChar = 'x';
            playerSprite.Attributes = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY;

            auto player = m_Scene.create_entity();
            player.add_component<TransformComponent>(glm::vec2(5, 5));
            player.add_component<SpriteComponent>(playerSprite);
            player.add_component<MovementComponent>();
            player.add_component<RigidbodyComponent>();
        }

        // Map:
        {
            constexpr uint32_t mapWidth = 80;
            constexpr uint32_t mapHeight = 30;

            m_Scene.create_entity();

            CHAR_INFO wall;
            wall.Char.AsciiChar = ' ';
            wall.Attributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY;

            for (uint32_t x = 0; x < mapWidth; ++x)
            {
                auto mapEntity = m_Scene.create_entity();
                mapEntity.add_component<TransformComponent>(glm::vec2(x, 0.f));
                mapEntity.add_component<SpriteComponent>(wall);
                auto& rb = mapEntity.add_component<RigidbodyComponent>();
                rb.isStatic = true;
            }

            for (uint32_t x = 0; x < mapWidth; ++x)
            {
                auto mapEntity = m_Scene.create_entity();
                mapEntity.add_component<TransformComponent>(glm::vec2(x, mapHeight - 1));
                mapEntity.add_component<SpriteComponent>(wall);
                auto& rb = mapEntity.add_component<RigidbodyComponent>();
                rb.isStatic = true;
            }

            for (uint32_t y = 0; y < mapHeight; ++y)
            {
                auto mapEntity = m_Scene.create_entity();
                mapEntity.add_component<TransformComponent>(glm::vec2(0.f, y));
                mapEntity.add_component<SpriteComponent>(wall);
                auto& rb = mapEntity.add_component<RigidbodyComponent>();
                rb.isStatic = true;
            }

            for (uint32_t y = 0; y < mapHeight; ++y)
            {
                auto mapEntity = m_Scene.create_entity();
                mapEntity.add_component<TransformComponent>(glm::vec2(mapWidth - 1, y));
                mapEntity.add_component<SpriteComponent>(wall);
                auto& rb = mapEntity.add_component<RigidbodyComponent>();
                rb.isStatic = true;
            }
        }
    }

    void ArenaScene::update(double dt)
    {
        update_player_movement(dt);

        update_collisions(dt);

        stop_movement();
    }

    void ArenaScene::render(amo::AmoraConsole* console)
    {
        for (auto [_, transform, sprite] : m_Scene.m_Registry.view<TransformComponent, SpriteComponent>().each())
            console->write((uint32_t)transform.position.x, (uint32_t)transform.position.y, sprite.data);
    }

    void ArenaScene::update_collisions(double dt)
    {
        auto movableView = m_Scene.m_Registry.view<TransformComponent, RigidbodyComponent, MovementComponent>();
        auto objectView = m_Scene.m_Registry.view<TransformComponent, RigidbodyComponent>();

        for (auto [moveEntity, transformMove, rigidbodyMove, _] : movableView.each())
        {
            if (rigidbodyMove.isStatic)
                continue;

            for (auto [objectView, transformObject, rigidbodyObject] : objectView.each())
            {
                if (moveEntity == objectView)
                    continue;

                if (glm::uvec2(transformMove.position) == glm::uvec2(transformObject.position))
                {
                    if (rigidbodyMove.velocity.x > 0)
                        transformMove.position.x -= 1;

                    if (rigidbodyMove.velocity.x < 0)
                        transformMove.position.x += 1;

                    if (rigidbodyMove.velocity.y < 0)
                        transformMove.position.y += 1;

                    if (rigidbodyMove.velocity.y > 0)
                        transformMove.position.y -= 1;
                }
            }
        }
    }

    void ArenaScene::update_player_movement(double dt)
    {
        auto view = m_Scene.m_Registry.view<TransformComponent, MovementComponent, RigidbodyComponent>();

        for (auto [_, transform, movement, rigidbody] : view.each())
        {
            if (GetAsyncKeyState(0x53) < 0)
            {
                rigidbody.velocity.y += rigidbody.speed * (float)dt;
                movement.direction = Direction::BOTTOM;
            }

            if (GetAsyncKeyState(0x57) < 0)
            {
                rigidbody.velocity.y -= rigidbody.speed * (float)dt;
                movement.direction = Direction::TOP;
            }

            if (GetAsyncKeyState(0x44) < 0)
            {
                rigidbody.velocity.x += rigidbody.speed * (float)dt;
                movement.direction = Direction::RIGHT;
            }

            if (GetAsyncKeyState(0x41) < 0)
            {
                rigidbody.velocity.x -= rigidbody.speed * (float)dt;
                movement.direction = Direction::LEFT;
            }

            transform.position.x += rigidbody.velocity.x;
            transform.position.y += rigidbody.velocity.y;
        }
    }

    void ArenaScene::stop_movement()
    {
        auto view = m_Scene.m_Registry.view<TransformComponent, MovementComponent, RigidbodyComponent>();

        for (auto [_, transform, movement, rigidbody] : view.each())
        {
            rigidbody.velocity.x = 0.f;
            rigidbody.velocity.y = 0.f;
        }
    }

    void ArenaScene::initialize_weapon()
    {
        weapons.push_back({ "Longsword", 10 });
        weapons.push_back({ "Katana", 10 });
        weapons.push_back({ "Scimitar", 10 });
    }

    Weapon ArenaScene::choose_weapon()
    {
        return weapons[Random<uint32_t>::get(0, (uint32_t)weapons.size() - 1)];
    }
}