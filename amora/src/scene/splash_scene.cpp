#pragma once
#include <algorithm>

#include "splash_scene.hpp"

#include "scene/scene_holder.hpp"
#include "console/console.hpp"
#include "utils/file.hpp"

namespace amo
{
	void SplashScene::initialize()
	{
		m_WelcomeArt = read_file("res/welcome_art.txt").value();
		m_WelcomeArtWidth = m_WelcomeArt.find_first_of("\n");
		m_WelcomeArtHeight = std::count(m_WelcomeArt.begin(), m_WelcomeArt.end(), '\n') + 1;
	}

	void SplashScene::update(double dt)
	{
		m_SelectTimerCurrent += dt;

		if (m_SelectTimerCurrent < m_SelectTimer)
			return;

		if (GetAsyncKeyState(VK_UP) < 0)
		{
			if (m_CurrentButton == ButtonLabel::PLAY)
				return;

			m_CurrentButton = static_cast<ButtonLabel>((int)m_CurrentButton - 1);
			m_SelectTimerCurrent = 0;
		}

		else if (GetAsyncKeyState(VK_DOWN) < 0)
		{
			if (m_CurrentButton == ButtonLabel::EXIT)
				return;

			m_CurrentButton = static_cast<ButtonLabel>((int)m_CurrentButton + 1);
			m_SelectTimerCurrent = 0;
		}

		else if (GetAsyncKeyState(VK_RETURN) < 0)
		{
			switch (m_CurrentButton)
			{
				case ButtonLabel::PLAY:
				{
					holder->set_current(1);
				} break;
					
				case ButtonLabel::CONFIG:
					/* IMPLEMENT */
					break;

				case ButtonLabel::EXIT:
					exit(0);
					break;
			}
		}
	}

	void SplashScene::render(amo::AmoraConsole* console)
	{
		render_header(console);

		render_buttons(console);
	}

	void SplashScene::render_header(amo::AmoraConsole* console)
	{
		uint32_t x = console->get_width() / 2 - m_WelcomeArtWidth / 2;
		uint32_t y = m_WelcomeArtYPadding;

		console->write_text_blob(
			m_WelcomeArt,
			{ x, y },
			m_Attributes
		);
	}

	void SplashScene::render_buttons(amo::AmoraConsole* console)
	{
		constexpr uint32_t yPadding = 3;

		// Play Button:
		{
			uint32_t attribute = m_CurrentButton == ButtonLabel::PLAY ? m_SelectedAttributes : m_Attributes;

			std::string text = "----# | PLAY | #----";
			uint32_t x = console->get_width() / 2 - text.length() / 2;
			uint32_t y = m_WelcomeArtHeight + m_WelcomeArtYPadding + yPadding;

			console->write_text(text, { x, y }, attribute);
		}
		
		// Config Button:
		uint32_t configPadding = yPadding;
		{
			uint32_t attribute = m_CurrentButton == ButtonLabel::CONFIG ? m_SelectedAttributes : m_Attributes;

			std::string text = "----# | CONFIG | #----";
			uint32_t x = console->get_width() / 2 - text.length() / 2;
			uint32_t y = m_WelcomeArtHeight + m_WelcomeArtYPadding + yPadding + configPadding;

			console->write_text(text, { x, y }, attribute);
		}

		// Exit Button:
		uint32_t exitPadding = configPadding + yPadding;
		{
			uint32_t attribute = m_CurrentButton == ButtonLabel::EXIT ? m_SelectedAttributes : m_Attributes;

			std::string text = "----# | EXIT | #----";
			uint32_t x = console->get_width() / 2 - text.length() / 2;
			uint32_t y = m_WelcomeArtHeight + m_WelcomeArtYPadding + yPadding + exitPadding;

			console->write_text(text, { x, y }, attribute);
		}
	}
}