#include <map>
#include <string>
#include <memory>
#include <iostream>

enum class Importance
{
    primary,
    secondary,
    tertiary,
};

template <typename T, typename Key = std::string>
class Multiton
{
    public:
        static std::shared_ptr<T> get(const Key& key)
        {
            if(const auto it = instances.find(key); it != instances.end())
            {
                return it->second;
            }

            auto instance  = std::make_shared<T>();
            instances[key] = instance;

            return instance;
        }

    protected:
        Multiton() = default;
        virtual ~Multiton() = default;

    private:
        static std::map<Key, std::shared_ptr<T>> instances;
};

template <typename T, typename Key>
std::map<Key, std::shared_ptr<T>> Multiton<T, Key>::instances;

class Printer
{
    public:
        Printer()
        {
            ++total_instance_count;

            std::cout << "A total of "
                      << Printer::total_instance_count
                      << " instances created so far.\n";
        }

    private:
        static int total_instance_count;
};

int Printer::total_instance_count = 0;

int main(int argc, char* argv[])
{
    using PrinterMultiton = Multiton<Printer, Importance>;

    auto main_printer      =  PrinterMultiton::get(Importance::primary);
    auto secondary_printer =  PrinterMultiton::get(Importance::secondary);
    auto tertiary_printer  =  PrinterMultiton::get(Importance::tertiary);

    return 0;
}
