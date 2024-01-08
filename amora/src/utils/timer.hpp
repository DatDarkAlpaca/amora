#pragma once

namespace amo
{
	class Timer
	{
	public:
		explicit Timer() = default;

		explicit Timer(double duration)
			: m_TimerDuration(duration)
		{

		}

	public:
		void set_timer(double duration) 
		{ 
			m_TimerDuration = duration; 
		}

		void update(double dt)
		{
			m_TimerCurrent += dt;
		}

		void reset() 
		{
			m_TimerCurrent = 0.0; 
		}

	public:
		inline bool complete() const { return m_TimerCurrent >= m_TimerDuration; }

	private:
		double m_TimerCurrent = 0.0, m_TimerDuration = 0.0;
	};
}