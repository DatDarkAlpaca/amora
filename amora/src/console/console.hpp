#pragma once
#include <functional>
#include <string>

#include "windows_header.h"

namespace amo
{
    class AmoraConsole
    {
        using EventCallback = std::function<void(INPUT_RECORD)>;

    public:
        explicit AmoraConsole(const std::string& title, uint32_t width, uint32_t height);

    public:
        void clear(const CHAR_INFO& clearChar);

    public:
        void set_event_callback(const EventCallback& eventCallback);

        void set_title(const std::string& title);

        void set_size(uint32_t width, uint32_t height);

    public:
        inline uint32_t get_input_event_amount() const;

        void poll_events();

    private:
        EventCallback m_EventCallback;
        HANDLE m_OutputHandle, m_InputHandle;

    private:
        uint32_t m_Width, m_Height;
        CHAR_INFO* m_Buffer;
    };
}