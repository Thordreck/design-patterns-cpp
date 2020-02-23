#include <string>
#include <vector>
#include <sstream>
#include <iostream>

struct HtmlElement
{
    std::string name;
    std::string text;

    std::vector<HtmlElement> elements;

    const size_t indent_size { 2 };

    HtmlElement() {}
    HtmlElement(const std::string& _name, const std::string& _text) : name(_name), text (_text)  {}

    std::string str(int _indent = 0) const
    {
        std::ostringstream oss;
        std::string i(indent_size * _indent, ' ');

        oss << i << "<" << name << ">" << std::endl;

        if(!text.empty())
        {
            oss << std::string(indent_size * (indent_size + 1), ' ') << text << std::endl;
        }

        for(const auto& e : elements)
        {
            oss << e.str(_indent + 1);
        }

        oss << i << "</" << name << ">" << std::endl;
        return oss.str();
    }
};

struct HtmlBuilder
{
    HtmlElement root;

    HtmlBuilder(const std::string& _root_name)
    {
        root.name = _root_name;
    }

    void add_child(const std::string& _child_name, const std::string& _child_text)
    {
        root.elements.emplace_back( _child_name, _child_text );
    }

    std::string str() const { return root.str(); }
};

int main()
{
    HtmlBuilder builder { "ul" };
    builder.add_child("li", "hello");
    builder.add_child("li", "world");

    std::cout << builder.str() << std::endl;

    return 0;
}
