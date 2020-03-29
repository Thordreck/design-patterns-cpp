#include <vector>
#include <string>
#include <iostream>
#include <sstream>

struct Token
{
    enum Type { integer, plus, minus, lparen, rparen } type;

    std::string text;

    friend std::ostream& operator<<(std::ostream& oss, const Token& token)
    {
        return oss << "'" << token.text << "'";
    }
};

std::vector<Token> lex(const std::string& input)
{
    std::vector<Token> result;

    for(size_t i = 0; i < input.size(); i++)
    {
        switch(input[i])
        {
            case '+':
                result.push_back( { Token::plus, "+" } );
                break;
            case '-':
                result.push_back( { Token::minus, "-" } );
                break;
            case '(':
                result.push_back( { Token::lparen, "(" } );
                break;
            case ')':
                result.push_back( { Token::rparen, ")" } );
                break;
            default:
                std::ostringstream buffer;
                buffer << input[i];
                for(size_t j = i + 1; j < input.size(); j++)
                {
                    if(std::isdigit(input[j]))
                    {
                        buffer << input[j];
                        ++i;
                    }
                    else
                    {
                        break;
                    }
                }

                result.push_back( { Token::integer, buffer.str() } );
        }
    }

    return result;
}

int main()
{
    std::string input { "(13-4)-(12+1)" };

    auto tokens = lex(input);

    for(auto& token : tokens)
    {
        std::cout << token << " ";
    }
    std::cout << "\n";

    return 0;
}
