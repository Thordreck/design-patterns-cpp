#include <iostream>
#include <sstream>
#include <variant>

struct AddressPrinter
{
    void operator()(const std::string& house_name) const
    {
        std::cout << "A house called " << house_name << "\n";
    }

    void operator()(const int house_number) const
    {
        std::cout << "House number " << house_number << "\n";
    }
};

int main()
{
    std::variant<std::string, int> house;

    house = "Montefiore Castle";

    AddressPrinter ap;
    std::visit(ap, house);

    // Instead of using a functor such as AddressPrinter we could
    // also use lambdas
    std::visit([](auto& arg)
    {
        using T = std::decay_t<decltype(arg)>;

        if constexpr (std::is_same_v<T, std::string>)
        {
            std::cout << "A house called " << arg << "\n";
        }
        else
        {
            std::cout << "House number " << arg << "\n";
        }

    }, house);

    return 0;
}
