#include "application/application.hpp"

class MainScene : public amo::IScene
{
public:
    void handle_event(INPUT_RECORD record) override
    {
        if (record.EventType != KEY_EVENT)
            return;

        if (record.Event.KeyEvent.wVirtualKeyCode == VK_SPACE)
            m_Pressed = !m_Pressed;
    }

    void render(amo::AmoraConsole* console) override
    {
        CHAR_INFO info;
        info.Char.AsciiChar = ' ';
        info.Attributes =
            BACKGROUND_BLUE   |
            BACKGROUND_GREEN  |
            BACKGROUND_RED    |
            BACKGROUND_INTENSITY;

        if (m_Pressed)
            info.Attributes =
            BACKGROUND_BLUE | BACKGROUND_INTENSITY;

        console->clear(info);
    }

private:
    bool m_Pressed = false;
};

int main()
{
    amo::Application app("Amora v1.0", 80, 50);
    app.add_scene(std::make_unique<MainScene>());

    app.run();
}