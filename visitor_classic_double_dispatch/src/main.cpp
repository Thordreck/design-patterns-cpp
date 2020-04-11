#include <iostream>
#include <sstream>

struct DoubleExpression;
struct AdditionExpression;
struct SubstractionExpression;

struct ExpressionVisitor
{
    virtual void visit(DoubleExpression* de)       = 0;
    virtual void visit(AdditionExpression* ae)     = 0;
    virtual void visit(SubstractionExpression* se) = 0;
};

struct Expression
{
    virtual ~Expression() = default;

    virtual void accept(ExpressionVisitor* visitor) = 0;
};

struct DoubleExpression : public Expression
{
    double value;

    DoubleExpression(double value) : value (value) {}


    void accept(ExpressionVisitor* visitor) override
    {
        visitor->visit(this);
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

    void accept(ExpressionVisitor* visitor) override
    {
        visitor->visit(this);
    }
};

struct SubstractionExpression : public Expression
{
    Expression* lhs;
    Expression* rhs;

    ~SubstractionExpression()
    {
        delete lhs;
        delete rhs;
    }

    SubstractionExpression(Expression* lhs, Expression* rhs)
        : lhs (lhs)
        , rhs (rhs)
    {}

    void accept(ExpressionVisitor* visitor) override
    {
        visitor->visit(this);
    }
};

struct ExpressionPrinter : public ExpressionVisitor
{
    std::ostringstream oss;

    void visit(DoubleExpression* de) override
    {
        oss << de->value;
    }

    void visit(AdditionExpression* ae) override
    {
        const bool need_braces = dynamic_cast<SubstractionExpression*>(ae->rhs);

        ae->lhs->accept(this);
        oss << "+";

        if(need_braces) { oss << "("; }
        ae->rhs->accept(this);
        if(need_braces) { oss << ")"; }
    }

    void visit(SubstractionExpression* se) override
    {
        const bool need_braces = dynamic_cast<SubstractionExpression*>(se->rhs);

        if(need_braces) { oss << "("; }
        se->lhs->accept(this);
        oss << "-";
        se->rhs->accept(this);
        if(need_braces) { oss << ")"; }
    }

    std::string str() const { return oss.str(); }
};

struct ExpressionEvaluator : public ExpressionVisitor
{
    double result;

    void visit(DoubleExpression* de) override
    {
        result = de->value;
    }

    void visit(AdditionExpression* ae) override
    {
        ae->lhs->accept(this);
        auto temp = result;
        ae->rhs->accept(this);
        result = temp - result;
    }

    void visit(SubstractionExpression* se) override
    {
        se->lhs->accept(this);
        auto temp = result;
        se->rhs->accept(this);
        result -= temp;
    }
};

int main()
{
    auto e = AdditionExpression
            { 
               new DoubleExpression { 1 },
               new SubstractionExpression
               {
                   new DoubleExpression { 2 },
                   new DoubleExpression { 3 }
               }
             };

    ExpressionPrinter ep;
    ep.visit(&e);

    std::cout << ep.str() << std::endl;

    ExpressionEvaluator evaluator;
    evaluator.visit(&e);

    std::cout << ep.str() << " = " << evaluator.result << std::endl;

    return 0;
}
