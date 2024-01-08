#include "console.hpp"
#include <cmath>
#include <sstream>

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
        
        m_ClearAttributes.Char.AsciiChar = ' ';
        m_ClearAttributes.Attributes = NULL;
    }

    void AmoraConsole::set_clear_attributes(const CHAR_INFO& info)
    {
        m_ClearAttributes = info;
    }

    void AmoraConsole::clear()
    {
        for (uint32_t i = 0; i < m_Width * m_Height; ++i)
        {
            m_Buffer[i].Char.AsciiChar = m_ClearAttributes.Char.AsciiChar;
            m_Buffer[i].Attributes = m_ClearAttributes.Attributes;
        }

        display();
    }

    void AmoraConsole::write(uint32_t x, uint32_t y, const CHAR_INFO& info)
    {
        uint32_t index = x + m_Width * y;
        if (index > m_Width * m_Height - 1 || index < 0)
            return;

        m_Buffer[x + m_Width * y] = info;
    }

    void AmoraConsole::write_line(const Vec2& start, const Vec2& end, const CHAR_INFO& info)
    {
        int dx = std::abs((int)end.x - (int)start.x);
        int sx = start.x < end.x ? 1 : -1;

        int dy = -std::abs((int)end.y - (int)start.y);
        int sy = start.y < end.y ? 1 : -1;

        int error = dx + dy;

        int x0 = start.x;
        int y0 = start.y;
        int x1 = end.x;
        int y1 = end.y;

        while (true)
        {
            write(x0, y0, info);

            if (x0 == x1 && y0 == y1)
                break;

            int error2 = 2 * error;
            if (error2 >= dy)
            {
                if (x0 == x1)
                    break;

                error += dy;
                x0 += sx;
            }
                
            if (error2 <= dx)
            {
                if (y0 == y1)
                    break;

                error += dx;
                y0 += sy;
            }
        }
    }

    void AmoraConsole::write_text_blob(const std::string& text, const Vec2& position, uint32_t attributes)
    {
        std::istringstream ss(text);

        std::string line;
        uint32_t index = 0;
        while (std::getline(ss, line)) 
        {
            write_text(line, { position.x, position.y + index }, attributes);
            ++index;
        }
    }

    void AmoraConsole::write_text(const std::string& text, const Vec2& position, uint32_t attributes)
    {
        uint32_t index = 0;
        for (const auto& character : text)
        {
            CHAR_INFO info;
            info.Char.AsciiChar = character;
            info.Attributes = attributes;

            write(position.x + index, position.y, info);
            ++index;
        }
    }

    void AmoraConsole::write_rect(const Rect& rect, const CHAR_INFO& info)
    {
        for (uint32_t y = rect.bottom; y < rect.top; ++y)
        {
            for (uint32_t x = rect.left; x <= rect.right; ++x)
                write(x, y, info);
        }
    }

    void AmoraConsole::display()
    {
        COORD charBufSize = { m_Width, m_Height };
        COORD characterPos = { 0, 0 };
        SMALL_RECT writeArea = { 0, 0, m_Width - 1, m_Height - 1 };

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
