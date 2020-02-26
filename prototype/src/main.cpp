#include <string>
#include <iostream>

struct Address
{
    std::string street;
    std::string city;

    int suite;

    Address(const std::string street, const std::string city, int suite)
        : street (street)
        , city   (city)
        , suite  (suite)
    {}

    Address(const Address& other)
        : street  (other.street)
        , city    (other.city)
        , suite   (other.suite)
    {}

    friend std::ostream& operator<<(std::ostream& os, const Address& address)
    {
        os << "street: " << address.street << " city: " << address.city
           << " suite: " << address.suite;

        return os;
    }
};

struct Contact
{
    std::string name;
    Address* address;

    Contact(const std::string &name, Address* address)
        : name    (name)
        , address (address)
    {}
    
    Contact(const Contact& other)
        : name    (other.name)
        , address { new Address { *other.address } }
    {}

    friend std::ostream& operator<<(std::ostream& os, const Contact& contact)
    {
        os << "name: " << contact.name << " address: " << *contact.address;

        return os;
    }
};

int main()
{
    Contact john { "John Doe", new Address { "123 East Dr", "London", 123 } };
    //Contact jane { "Jane Smith", { "123 East Dr", "London", 103 } };

    Contact jane = john;
    jane.name = "Jane Smith";
    jane.address->suite = 103;

    std::cout << john << std::endl << jane << std::endl;

    return 0;
}
