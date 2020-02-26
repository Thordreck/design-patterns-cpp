#include <string>
#include <memory>
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

    ~Contact()
    {
        delete address;
    }

    friend std::ostream& operator<<(std::ostream& os, const Contact& contact)
    {
        os << "name: " << contact.name << " address: " << *contact.address;

        return os;
    }
};

struct EmployeeFactory
{
    public:
        static std::unique_ptr<Contact> new_main_office_employee(const std::string& name,
                                                                const int suite)
        {
            static Contact p { "", new Address { "123 East Dr", "London", 0 }};

            return new_employee(name, suite, p);
        }

    private:
        static std::unique_ptr<Contact> new_employee(const std::string& name,
                                                     const int suite,
                                                     const Contact& prototype)
        {
            auto result = std::make_unique<Contact>(prototype);
            result->name = name;
            result->address->suite = suite;

            return result;
        }
};

int main()
{
    auto john = EmployeeFactory::new_main_office_employee("John", 123);
    auto jane = EmployeeFactory::new_main_office_employee("Jane", 102);

    std::cout << *john << std::endl << *jane << std::endl;

    return 0;
}
