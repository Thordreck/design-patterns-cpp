#include <string>
#include <vector>
#include <sstream>
#include <iostream>

struct Tag
{
    std::string name;
    std::string text;

    std::vector<Tag> children;
    std::vector<std::pair<std::string, std::string>> attributes;

    friend std::ostream& operator<<(std::ostream& os, const Tag& tag)
    {
        os << "<" << tag.name;

        for (const auto& att : tag.attributes)
        {
            os << " " << att.first << "=\"" << att.second << "\"";
        }

        if (tag.children.size() == 0 && tag.text.length() == 0)
        {
            os << "/>" << std::endl;
        } 
        else
        {
            os << ">" << std::endl;

            if (tag.text.length())
                os << tag.text << std::endl;

            for (const auto& child : tag.children)
                os << child;

            os << "</" << tag.name << ">" << std::endl;
        }

        return os;
    }

    protected:

    Tag(const std::string& _name, const std::string& _text) : name(_name), text(_text) {}
    Tag(const std::string& _name, const std::vector<Tag>& _children) : name(_name), children(_children) {}
};

struct P : public Tag
{
    P(const std::string& _text) : Tag("p", _text) {}
    P(std::initializer_list<Tag> _children) : Tag("p", _children) {}
};

struct IMG : public Tag
{
    explicit IMG(const std::string& _url) : Tag("img", "")
    {
        attributes.emplace_back(std::make_pair("src", _url));
    }
};

int main()
{
    std::cout <<
        P
        {
            IMG { "http://pokemon.com/pikachu.png" }
        }
        << std::endl;

    return 0;
}
