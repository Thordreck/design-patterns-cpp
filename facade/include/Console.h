#ifndef CONSOLE_H
#define CONSOLE_H

#include <iostream>
#include <string>
#include <vector>
#include <memory>

#include "Window.h"
#include "TextBuffer.h"

class Console
{
    public:
        static Console& instance()
        {
            static Console console;
            return console;
        }

        std::vector<std::shared_ptr<Window>> windows;

        std::shared_ptr<Window> multicolumn (const std::string& title,
                                             uint8_t columnCount,
                                             uint8_t columnWidth,
                                             uint8_t charsHigh)
        {
            auto w = std::make_shared<Window>(title, columnCount * columnWidth * charWidth, charsHigh);

            for(uint8_t c = 0; c < columnCount; c++)
            {
                auto buffer = std::make_shared<TextBuffer>(columnWidth, charsHigh);
                w->buffers.push_back(buffer);

                auto viewport = std::make_shared<Viewport>(buffer, buffer->get_size());
                w->viewports.push_back(viewport);

                windows.push_back(w);
            }

            return w;
        }

    private:
        Console() {};

        Console(const Console&)        = delete;
        void operator=(const Console&) = delete;

    private:
        const int charWidth  = 10;
        const int charHeight = 14;
};

#endif // CONSOLE_H
