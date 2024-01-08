#pragma once
#include <utils/timer.hpp>
#include <core/scene.hpp>
#include <numeric>
#include <string>

namespace amo
{
    class SplashScene : public amo::IScene
    {
        enum class ButtonLabel
        {
            PLAY        = 0,
            CONFIG      = 1,
            EXIT        = 2
        };

    public:
        void initialize() override;

        void update(double dt) override;

        void render(amo::AmoraConsole* console) override;

    private:
        void render_header(amo::AmoraConsole* console);

        void render_buttons(amo::AmoraConsole* console);

    private:
        std::string m_WelcomeArt;
        uint32_t m_WelcomeArtWidth = 0;
        uint32_t m_WelcomeArtHeight = 0;
        uint32_t m_WelcomeArtYPadding = 2;
        uint32_t m_Attributes = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY;

    private:
        uint32_t m_SelectedAttributes = FOREGROUND_RED | FOREGROUND_INTENSITY;
        ButtonLabel m_CurrentButton;
        Timer m_Timer;
    };
}