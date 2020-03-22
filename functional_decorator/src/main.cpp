#include <string>
#include <iostream>
#include <functional>

struct Logger
{
    std::function<void()> func;
    std::string name;

    Logger(const std::function<void()>& func, std::string name)
        : func (func)
        , name (std::move(name))
    {}

    void operator()() const
    {
        std::cout << "Entering " << name << std::endl;
        func();
        std::cout << "Exiting " << name << std::endl;
    }
};

template <class Func>
struct Logger2
{
    Func func;
    std::string name;

    Logger2(const Func& func, std::string name)
        : func (func)
        , name (std::move(name))
    {}

    void operator()() const
    {
        std::cout << "Entering " << name << std::endl;
        func();
        std::cout << "Exiting " << name << std::endl;
    }
};

// Note: this factory function is needed if you are not using C++17, as the type
// of the functor cannot be infered from the invocation of the constructor.
template <typename Func>
auto make_logger2(Func func, const std::string& name)
{
    return Logger2<Func>{ func, name };
}

// What if we use functors with arguments that return values?
double add(double a, double b)
{
    std::cout << a << " + " <<  b << " = " << (a + b) << std::endl;
    return a + b;
}

template <typename> struct Logger3;

template <typename R, typename... Args>
struct Logger3<R(Args...)>
{
    std::function<R(Args...)> func;
    std::string name;

    Logger3(const std::function<R(Args...)>& func, std::string name)
        : func(func)
        , name(std::move(name))
    {}

    R operator() (Args ...args)
    {
        std::cout << "Entering " << name << std::endl;
        R result = func(args...);
        std::cout << "Exiting " << name << std::endl;

        return result;
    }
};

template <typename R, typename... Args>
auto make_logger3(R(*func)(Args...), const std::string& name)
{
    return Logger3<R(Args...)>(std::function<R(Args...)>(func), name);
}

int main()
{
    Logger([] () { std::cout << "Hello" << std::endl; }, "HelloFunction")();
    Logger2([] () { std::cout << "Hello" << std::endl; }, "HelloFunction")();

    auto log = make_logger2([]() { std::cout << "Hello" << std::endl; }, "HelloFunction");
    log();

    auto logged_add = make_logger3(add, "add");

    auto result = logged_add(2, 3);
    std::cout << "Result: " << result << std::endl;

    return 0;
}
