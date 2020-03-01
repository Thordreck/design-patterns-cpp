#include <string>
#include <iostream>

#include <boost/di.hpp>
#include <boost/lexical_cast.hpp>

struct IFoo
{
    virtual std::string name() = 0;
};

struct Foo : public IFoo
{
    static int id;

    Foo() { ++id; }
    std::string name() override
    {
        using namespace std::string_literals;

        return "foo "s + boost::lexical_cast<std::string>(id);
    }
};

int Foo::id = 0;

struct Bar
{
    std::shared_ptr<IFoo> foo;
};

int main(int argc, char* argv[])
{
    auto injector = boost::di::make_injector(
            boost::di::bind<IFoo>().to<Foo>().in(boost::di::singleton)
            );

    auto bar1 = injector.create<std::shared_ptr<Bar>>();
    auto bar2 = injector.create<std::shared_ptr<Bar>>();

    std::cout << bar1->foo->name() << std::endl;
    std::cout << bar2->foo->name() << std::endl;

    std::cout << std::boolalpha
              << (bar1->foo.get() == bar2->foo.get())
              << std::endl;

    return 0;
}
