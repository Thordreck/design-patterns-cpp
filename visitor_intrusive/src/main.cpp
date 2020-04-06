#include <iostream>
#include <sstream>

struct Expression
{
    virtual ~Expression() = default;

    // Note: this kind of visitor breaks the
    // open close principle
    virtual void print(std::ostringstream& oss) = 0;
};

struct DoubleExpression : public Expression
{
    double value;

    DoubleExpression(double value) : value (value) {}

    void print(std::ostringstream& oss) override
    {
        oss << value;
    }
};

struct AdditionExpression : public Expression
{
    Expression* lhs;
    Expression* rhs;

    ~AdditionExpression()
    {
        delete lhs;
        delete rhs;
    }

    AdditionExpression(Expression* lhs, Expression* rhs)
        : lhs (lhs)
        , rhs (rhs)
    {}

    void print(std::ostringstream& oss) override
    {
        oss << "(";
        lhs->print(oss);
        oss << "+";
        rhs->print(oss);
        oss << ")";
    }
};

int main()
{
    auto e = AdditionExpression { new DoubleExpression { 1 },
                                   new AdditionExpression
                                   {
                                       new DoubleExpression { 2 },
                                       new DoubleExpression { 3 }
                                   }
                                 };

    std::ostringstream oss;
    e.print(oss);

    std::cout << oss.str() << std::endl;

    return 0;
}
