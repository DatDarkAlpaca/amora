#pragma once
#include <core/view.hpp>
#include <utils/timer.hpp>
#include <numeric>

namespace amo
{
    class SystemOverlay : public amo::IView
    {
    public:
        void initialize() override;

        void update(double dt) override;

        void render(amo::AmoraConsole* console) override;

    private:
        Timer m_Timer;
        bool m_OverlayActive = false;
    };
}