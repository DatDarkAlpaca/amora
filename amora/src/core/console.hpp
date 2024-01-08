#pragma once
#include <functional>
#include <string>

#include "windows_header.hpp"
#include "utils/rect.hpp"
#include "utils/vec2.hpp"

namespace amo
{
    class AmoraConsole
    {
        using EventCallback = std::function<void(INPUT_RECORD)>;

    public:
        explicit AmoraConsole(const std::string& title, uint32_t width, uint32_t height);

    public:
        void set_clear_attributes(const CHAR_INFO& info);

        void clear();

    public:
        void write(uint32_t x, uint32_t y, const CHAR_INFO& info);

        void write_line(const vec2u& start, const vec2u& end, const CHAR_INFO& info);

        void write_text_blob(const std::string& text, const vec2u& position, uint32_t attributes = 0);

        void write_text(const std::string& text, const vec2u& position, uint32_t attributes = 0);

        void write_rect(const Rect& rect, const CHAR_INFO& info);

        void display();

    public:
        void set_event_callback(const EventCallback& eventCallback);

        void set_title(const std::string& title);

        void set_size(uint32_t width, uint32_t height);

    public:
        inline uint32_t get_input_event_amount() const;

        void poll_events();

    public:
        inline uint32_t get_width() const { return m_Width; }

        inline uint32_t get_height() const { return m_Height; }

    private:
        EventCallback m_EventCallback;
        HANDLE m_OutputHandle, m_InputHandle;

    private:
        uint32_t m_Width, m_Height;
        CHAR_INFO* m_Buffer;

    private:
        CHAR_INFO m_ClearAttributes;
    };
}