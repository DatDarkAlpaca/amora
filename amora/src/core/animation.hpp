#pragma once
#include <glm/glm.hpp>
#include <string>

#include "common.hpp"
#include "core/console.hpp"
#include "utils/frame.hpp"
#include "utils/timer.hpp"

namespace amo
{
	// 2. look through frames and frame duration
	// 3. update

	class Animation
	{
	public:
		explicit Animation() = default;

		Animation(const std::string& filepath, bool playOnlyOnce = false)
		{
			initialize(filepath, playOnlyOnce);
		}

	public:
		void initialize(const std::string& filepath, bool playOnlyOnce = false)
		{
			m_PlayOnlyOnce = playOnlyOnce;
			m_Frames = read_animation_file(filepath);

			m_CurrentFrame = &m_Frames[0];
			m_CurrentIndex = 0;

			m_Timer.set_timer(m_CurrentFrame->duration);
		}

	public:
		void set_position(const glm::vec2& position)
		{
			m_Position = position;
		}

	public:
		void update(double dt)
		{
			if (m_AnimationOver && m_PlayOnlyOnce)
				return;

			m_Timer.update(dt * 1000);

			if (m_Timer.complete())
			{
				// Determine next frame:
				size_t index = ((size_t)m_CurrentIndex++) % m_Frames.size();

				if (m_PlayOnlyOnce && index == m_Frames.size() - 1)
					m_AnimationOver = true;

				// Next frame:
				m_CurrentFrame = &m_Frames[index];
				m_Timer.set_timer(m_CurrentFrame->duration);
				m_Timer.reset();
			}
		}

		void render(NON_OWNING AmoraConsole* console)
		{
			console->write_text_blob(m_CurrentFrame->frameData, m_Position, FOREGROUND_RED);
		}

	public:
		bool complete() const { return m_AnimationOver && m_PlayOnlyOnce; }

	private:
		Timer m_Timer;
		glm::vec2 m_Position;

		bool m_PlayOnlyOnce;
		bool m_AnimationOver = false;

	private:
		std::vector<Frame> m_Frames;
		uint32_t m_CurrentIndex = 0;
		NON_OWNING Frame* m_CurrentFrame = nullptr;
	};
}