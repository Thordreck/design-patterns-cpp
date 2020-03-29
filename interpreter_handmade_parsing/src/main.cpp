#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <memory>

#include <boost/lexical_cast.hpp>

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

struct Element
{
    using Ptr = std::shared_ptr<Element>;

    virtual int eval() const = 0;
};

struct Integer : Element
{
    int value;

    Integer(int value) : value (value) {};

    int eval() const override
    {
        return value;
    }
};

struct BinaryOp : Element
{
    enum Type { addition, substraction } type;

    Element::Ptr lhs;
    Element::Ptr rhs;

    int eval() const override
    {
        if(type == addition)
        {
            return lhs->eval() + rhs->eval();
        }
        else
        {
            return lhs->eval() - rhs->eval();
        }
    }
};

Element::Ptr parse(const std::vector<Token>& tokens)
{
    auto result = std::make_shared<BinaryOp>();

    bool have_lhs { false };

    for(size_t i = 0; i < tokens.size(); i++)
    {
        auto token = tokens[i];
        
        switch(token.type)
        {
            case Token::integer:
            {
                int value = boost::lexical_cast<int>(token.text);
                if(!have_lhs)
                {
                    result->lhs = std::make_shared<Integer>(value);
                    have_lhs = true;
                }
                else
                {
                    result->rhs = std::make_shared<Integer>(value);
                }

            }
                break;
            case Token::plus:
                result->type = BinaryOp::addition;
                break;
            case Token::minus:
                result->type = BinaryOp::substraction;
                break;
            case Token::lparen:
            {
                size_t j = i;
                for(; j < tokens.size(); ++j)
                {
                    if(tokens[j].type == Token::rparen)
                    {
                        break;
                    }
                }

                std::vector<Token> subexpression(&tokens[i + 1], &tokens[j]);
                auto element = parse(subexpression);

                if(!have_lhs)
                {
                    result->lhs = element;
                    have_lhs = true;
                }
                else
                {
                    result->rhs = element;
                }

                i = j;
            }
                break;
            case Token::rparen:
                break;
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

    try
    {
        auto parsed = parse(tokens);
        std::cout << input << " = " << parsed->eval() << std::endl;
    }
    catch(const std::exception& ex)
    {
        std::cout << ex.what() << std::endl;
    }

    return 0;
}
