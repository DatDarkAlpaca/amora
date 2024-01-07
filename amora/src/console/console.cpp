#include "console.hpp"

namespace amo
{
    AmoraConsole::AmoraConsole(const std::string& title, uint32_t width, uint32_t height)
        : m_Width(width)
        , m_Height(height)
    {
        m_OutputHandle = GetStdHandle(STD_OUTPUT_HANDLE);
        m_InputHandle = GetStdHandle(STD_INPUT_HANDLE);

        set_title(title);
        set_size(width, height);

        m_Buffer = (CHAR_INFO*)calloc(width * height, sizeof(CHAR_INFO));
        printf("\n");
    }

    void AmoraConsole::clear(const CHAR_INFO& clearChar)
    {
        for (uint32_t i = 0; i < m_Width * m_Height; ++i)
        {
            m_Buffer[i].Char.AsciiChar = clearChar.Char.AsciiChar;
            m_Buffer[i].Attributes = clearChar.Attributes;
        }

        COORD charBufSize = { m_Width, m_Height };
        COORD characterPos = { 0, 0 };
        SMALL_RECT writeArea = { 0, 0, m_Width - 1, m_Height - 1 };

        // Write the characters:
        WriteConsoleOutputA(m_OutputHandle, m_Buffer, charBufSize, characterPos, &writeArea);
    }

    void AmoraConsole::set_event_callback(const EventCallback& eventCallback)
    {
        m_EventCallback = eventCallback;
    }

    void AmoraConsole::set_title(const std::string& title)
    {
        std::wstring titleStr(title.begin(), title.end());
        SetConsoleTitle(titleStr.c_str());
    }

    void AmoraConsole::set_size(uint32_t width, uint32_t height)
    {
        m_Width = width;
        m_Height = height;

        COORD bufferSize = { width, height };
        SetConsoleScreenBufferSize(m_OutputHandle, bufferSize);
    }

    inline uint32_t AmoraConsole::get_input_event_amount() const
    {
        DWORD numEvents;
        GetNumberOfConsoleInputEvents(m_InputHandle, &numEvents);
        return static_cast<uint32_t>(numEvents);
    }

    void AmoraConsole::poll_events()
    {
        unsigned long eventsReadAmount = 0;

        uint32_t eventAmount = get_input_event_amount();
        if (!eventAmount)
            return;

        INPUT_RECORD* eventBuffer = new INPUT_RECORD[eventAmount];
        ReadConsoleInput(m_InputHandle, eventBuffer, eventAmount, &eventsReadAmount);

        for (unsigned long i = 0; i < eventsReadAmount; ++i)
            m_EventCallback(eventBuffer[i]);

        delete[] eventBuffer;
    }
}
