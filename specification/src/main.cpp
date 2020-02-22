#include <vector>
#include <iostream>
#include <algorithm>

enum class Color { red,   green,  blue  };
enum class Size  { small, medium, large };

struct Product
{
    std::string name;
    Color       color;
    Size        size;
};

// Spefications
template <typename T>
struct Specification;

template <typename T>
struct AndSpecification : Specification<T>
{
    Specification<T>& first;
    Specification<T>& second;

    AndSpecification(Specification<T>& _first, Specification<T>& _second) : first(_first), second(_second) {}

    bool is_satisfied(T* _item) override
    {
        return first.is_satisfied(_item) && second.is_satisfied(_item);
    }
};
template <typename T>
struct Specification
{
    virtual bool is_satisfied(T* _item) = 0;

    AndSpecification<T> operator&&(Specification<T>&& other)
    {
        return AndSpecification<T>(*this, other);
    }
};

struct ColorSpecification : Specification<Product>
{
    Color color;

    ColorSpecification(Color color) : color(color) {};

    bool is_satisfied(Product* _item) override
    {
        return _item->color == color;
    }
};

struct SizeSpecification : Specification<Product>
{
    Size size;

    SizeSpecification(Size size) : size(size) {};

    bool is_satisfied(Product* _item) override
    {
        return _item->size == size;
    }
};

// Filters
template <typename T>
struct Filter
{
    virtual std::vector<T*> filter(const std::vector<T*> _items,
                                   Specification<T>& _spec) = 0;
};

struct BetterFilter : Filter<Product>
{
    std::vector<Product*> filter(const std::vector<Product*> _items,
                                 Specification<Product>& _spec) override
    {
        std::vector<Product*> results;
        std::copy_if(_items.cbegin(), _items.cend(), std::back_inserter(results),
                     [&] (Product* _item) { return _spec.is_satisfied(_item); } );

        return results;
    }
};

int main()
{
    Product apple { "Apple", Color::green, Size::small };
    Product tree  { "Tree",  Color::green, Size::large };
    Product house { "House", Color::blue,  Size::large };

    std::vector<Product*> items { &apple, &tree, &house };

    BetterFilter       filter;
    ColorSpecification green_spec(Color::green);

    for(const auto& item : filter.filter(items, green_spec))
    {
        std::cout << item->name << " is green." << std::endl;
    }

    SizeSpecification large_spec(Size::large);

    for(const auto& item : filter.filter(items, large_spec))
    {
        std::cout << item->name << " is large." << std::endl;
    }

    //AndSpecification<Product> green_large_spec(green_spec, large_spec);
    auto green_large_spec = green_spec && std::move(large_spec);

    for(const auto& item : filter.filter(items, green_large_spec))
    {
        std::cout << item->name << " is green and large." << std::endl;
    }

    return 0;
}
