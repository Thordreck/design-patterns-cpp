#include <iostream>
#include <algorithm>

struct Document;

// Interface not segregated
struct IMachine
{
    virtual void print(Document& _doc) = 0;
    virtual void scan(Document& _doc)  = 0;
    virtual void fax(Document& _doc)   = 0;
};

struct MFP : IMachine
{
    void print(Document& _doc) override
    {
    }

    void scan(Document& _doc)  override
    {
    }

    void fax(Document& _doc)   override
    {
    }
};

struct BadDesignedScanner : IMachine
{
    void print(Document& _doc) override
    {
    }

    void scan(Document& _doc)  override
    {
    }

    void fax(Document& _doc)   override
    {
    }
};

struct IPrinter
{
    virtual void print(Document& _doc) = 0;
};

struct IScanner
{
    virtual void scan(Document& _doc) = 0;
};

struct IFax
{
    virtual void fax(Document& _doc) = 0;
};

struct Scanner : IScanner
{
    void scan(Document& _doc)  override
    {
    }
};

int main()
{
    return 0;
}
