#include <iostream>
#include <sstream>

struct Expression
{
    virtual ~Expression() = default;
};

struct DoubleExpression : public Expression
{
    double value;

    DoubleExpression(double value) : value (value) {}
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
};

struct ExpressionPrinter
{
    std::ostringstream oss;

    void print(Expression* e)
    {
        if(auto de = dynamic_cast<DoubleExpression*>(e))
        {
            oss << de->value;
        }
        else if(auto ae = dynamic_cast<AdditionExpression*>(e))
        {
            oss << "(";
            print(ae->lhs);
            oss << "+";
            print(ae->rhs);
            oss << ")";
        }
    }

    std::string str() const { return oss.str(); }
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

    ExpressionPrinter ep;
    ep.print(&e);

    std::cout << ep.str() << std::endl;

    return 0;
}
