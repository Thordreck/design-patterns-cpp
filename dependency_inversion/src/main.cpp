#include <tuple>
#include <vector>
#include <iostream>
#include <algorithm>
#include <string_view>

enum class Relationship
{
    parent,
    child,
    sibling
};

struct Person
{
    std::string name;
};

struct RelationshipBrowser
{
    virtual std::vector<Person> find_all_children_of(std::string_view) = 0;
};

struct Relationships : RelationshipBrowser // Low-level module
{
    std::vector<std::tuple<Person, Relationship, Person>> relations;

    void add_parent_and_child(const Person& _parent, const Person& _child)
    {
        relations.emplace_back(_parent, Relationship::parent, _child);
        relations.emplace_back(_child,  Relationship::child, _parent);
    }

    std::vector<Person> find_all_children_of(std::string_view _name) override
    {
        std::vector<Person> result;

        for(auto&& [first, rel, second] : relations)
        {
            if(rel == Relationship::child && second.name == _name)
            {
                result.push_back(first);
            }
        }

        return result;
    }
};

// The Research class below is not well designed. It depends on the
// details of a lower level module (the internal structure of the Relationships class)
struct BadDesignedResearch // high-level
{
    BadDesignedResearch(Relationships& _relationships)
    {
        auto& relations = _relationships.relations;

        for(auto&& [first, rel, second] : relations)
        {
            if(rel == Relationship::parent)
            {
                std::cout << first.name << " has a child called " << second.name << std::endl;
            }
        }
    }
};

struct Research
{
    Research(RelationshipBrowser& _browser)
    {
        for(const auto& child : _browser.find_all_children_of("John"))
        {
            std::cout << "John has a child called " << child.name << std::endl;
        }
    }
};

int main()
{
    Person parent { "John" };
    Person child1 { "Chris" };
    Person child2 { "Matt" };

    Relationships relationships;
    relationships.add_parent_and_child(parent, child1);
    relationships.add_parent_and_child(parent, child2);

    BadDesignedResearch bad_research { relationships };

    std::cout << "-------------------------" << std::endl;

    Research research { relationships };

    return 0;
}
