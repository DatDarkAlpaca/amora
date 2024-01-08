#include "system_overlay.hpp"
#include <core/console.hpp>

namespace amo
{
	void SystemOverlay::initialize()
	{
		m_Timer.set_timer(0.20);
	}

	void SystemOverlay::update(double dt)
	{
		m_Timer.update(dt);

		if (!m_Timer.complete())
			return;

		if (GetAsyncKeyState(VK_F12) < 0)
		{
			m_OverlayActive = !m_OverlayActive;
			m_Timer.reset();
		}
	}
	void SystemOverlay::render(amo::AmoraConsole* console)
	{
		if (!m_OverlayActive)
			return;

		console->write_text("Overlay Active", { 0, 0 }, BACKGROUND_RED | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	}
}