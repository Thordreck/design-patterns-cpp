#include <map>
#include <string>
#include <sstream>
#include <iostream>

#include <boost/bimap.hpp>
#include <boost/flyweight.hpp>

// Bad implementation
struct BadUser
{
    std::string name;
};

// Flyweight implementation
using key = uint32_t;

struct User
{
    User(const std::string& _first_name, const std::string& _last_name)
        : first_name_ { add(_first_name) }
        , last_name_  { add(_last_name) }
    {}

    const std::string& first_name() const
    {
        return names.left.find(first_name_)->second;
    }

    const std::string& last_name() const
    {
        return names.left.find(last_name_)->second;
    }

    protected:
        static key add(const std::string& s)
        {
            auto it = names.right.find(s);

            if(it == names.right.end())
            {
                key id = ++seed;
                names.insert( { seed, s } );
                return id;
            }

            return it->second;
        }

    protected:
        const key first_name_;
        const key last_name_;

        static boost::bimap<key, std::string> names;
        static key seed;
};

key User::seed { 0 };
boost::bimap<key, std::string> User::names {};

std::ostream& operator<<(std::ostream& oss, const User& user)
{
    oss << "First name: " << user.first_name()
        << " last name: " << user.last_name();

    return oss;
}

struct BoostUser
{
    boost::flyweight<std::string> first_name;
    boost::flyweight<std::string> last_name;

    BoostUser(const std::string& first_name, const std::string& last_name)
        : first_name { first_name }
        , last_name  { last_name }
    {}
};

int main()
{
    // Bad implementation
    BadUser user1 { "John Doe" };
    BadUser user2 { "John Smith" };

    // Flyweight implementation
    User user3 { "John", "Smith" };
    User user4 { "Jane", "Smith" };

    std::cout << user3 << std::endl;
    std::cout << user4 << std::endl;

    BoostUser user5 { "John", "Smith" };
    BoostUser user6 { "Jane", "Smith" };

    std::cout << user5.first_name << std::endl;
    std::cout << user6.first_name << std::endl;

    std::cout << std::boolalpha
              << (&user5.first_name.get() == &user6.first_name.get()) << std::endl
              << (&user5.last_name.get() == &user6.last_name.get()) << std::endl;

    return 0;
}
