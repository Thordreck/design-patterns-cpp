#include <string>
#include <iostream>
#include <functional>

#include "Console.h"

int main()
{
    auto window = Console::instance().multicolumn("Test", 2, 40, 40);

    for(size_t i = 0; i < 40; i++)
    {
        window->buffers[1]->add_string(std::string { "This is line " }
                + boost::lexical_cast<std::string>(i), (i % 2 == 0));
    }

    window->Show();

    return 0;
}
