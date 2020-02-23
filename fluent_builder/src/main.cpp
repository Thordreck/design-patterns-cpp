#include <string>
#include <vector>
#include <sstream>
#include <iostream>

class HtmlElement
{
    friend class HtmlBuilder;

    public:
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

    private:
        HtmlElement() {}
        HtmlElement(const std::string& _name, const std::string& _text) : name(_name), text (_text)  {}

    private:
        std::string name;
        std::string text;

        std::vector<HtmlElement> elements;

        const size_t indent_size { 2 };
};

class HtmlBuilder
{
    public:
        HtmlBuilder(const std::string& _root_name)
        {
            root.name = _root_name;
        }

        HtmlBuilder& add_child(const std::string& _child_name, const std::string& _child_text)
        {
            HtmlElement element(_child_name, _child_text);
            root.elements.push_back(element);

            return *this;
        }

        std::string str() const { return root.str(); }

        operator HtmlElement() const
        {
            return root;
        }

    private:
        HtmlElement root;
};

int main()
{
    HtmlBuilder builder { "ul" };
    builder.add_child("li", "hello").add_child("li", "world");

    std::cout << builder.str() << std::endl;

    return 0;
}
