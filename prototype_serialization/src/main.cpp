#include <string>
#include <memory>
#include <sstream>
#include <iostream>

#include <boost/serialization/serialization.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>

struct Address
{
    std::string street;
    std::string city;

    int suite;

    Address() = default;

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

    private:
        friend class boost::serialization::access;

        template <class archive>
        void serialize(archive& ar, const unsigned version)
        {
            ar & street;
            ar & city;
            ar & suite;
        }
};

struct Contact
{
    std::string name;
    Address* address;

    Contact() = default;

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

    private:
        friend class boost::serialization::access;

        template <class archive>
        void serialize(archive& ar, const unsigned version)
        {
            ar & name;
            ar & address;
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
    auto clone = [] (const Contact& c)
    {
        std::ostringstream oss;
        boost::archive::text_oarchive oa(oss);
        oa << c;

        std::cout << oss.str() << std::endl;

        std::istringstream iss(oss.str());
        boost::archive::text_iarchive ia(iss);

        Contact result;
        ia >> result;

        return result;
    };

    auto john = EmployeeFactory::new_main_office_employee("John", 123);
    auto jane = clone(*john);

    jane.name = "Jane";

    std::cout << "John: " << *john << std::endl;
    std::cout << "Jane: " << jane << std::endl;

    return 0;
}
