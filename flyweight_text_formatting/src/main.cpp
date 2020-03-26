#include <map>
#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <cctype>
#include <algorithm>

//#include <boost/bimap.hpp>
//#include <boost/flyweight.hpp>

class FormattedText
{
    public:
        FormattedText(const std::string& plain_text)
            : plain_text (plain_text)
            , caps(plain_text.size(), false)
        {}

        void capitalize(size_t start, size_t end)
        {
            for(size_t i = start; i <= end; i++)
            {
                caps[i] = true;
            }
        }

        friend std::ostream& operator<<(std::ostream& oss, const FormattedText& obj)
        {
            std::string s;

            for(size_t i = 0; i < obj.plain_text.length(); i++)
            {
                char c = obj.plain_text[i];
                s+= obj.caps[i] ? std::toupper(c) : c;
            }

            return oss << s;
        }

    private:
        std::string plain_text;
        std::vector<bool> caps;
};

class BetterFormattedText
{
    public:
        struct TextRange
        {
            int start;
            int end;
            bool capitalize;

            bool covers(int position) const
            {
                return position >= start
                    && position <= end;
            }
        };

        TextRange& get_range(int start, int end)
        {
            formatting.emplace_back(TextRange{ start, end});
            return *formatting.rbegin();
        }

        BetterFormattedText(const std::string& text)
            : plain_text ( text )
        {}

        friend std::ostream& operator<<(std::ostream& oss, const BetterFormattedText& obj)
        {
            std::string s;

            for(size_t i = 0; i < obj.plain_text.length(); i++)
            {
                auto c = obj.plain_text[i];

                for(const auto& rng : obj.formatting)
                {
                    if(rng.covers(i) && rng.capitalize)
                    {
                        c = toupper(c);
                    }

                    s += c;
                }
            }

            return oss << s;
        }

    private:
        std::string plain_text;
        std::vector<TextRange> formatting;
};

int main()
{
    FormattedText ft { "This is a brave new world" };
    ft.capitalize(10, 15);

    std::cout << ft << std::endl;

    BetterFormattedText bft { "This is a brave new world" };
    bft.get_range(10, 15).capitalize = true;

    std::cout << bft << std::endl;

    return 0;
}
