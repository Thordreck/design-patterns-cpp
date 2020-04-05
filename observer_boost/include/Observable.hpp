#ifndef OBSERVABLE_HPP
#define OBSERVABLE_HPP

#include <string>
#include <vector>
#include <algorithm>

#include <boost/signals2.hpp>

using namespace boost::signals2;

template <typename> struct Observer;

template <class T>
class Observable
{
    public:
        void notify(T& source, const std::string& field_name)
        {
            for(auto* observer : observers)
            {
                observer->field_changed(source, field_name);
            }
        }

        void subscribe(Observer<T>& observer)
        {
            observers.push_back(&observer);
        }

        void unsubscribe(Observer<T>& observer)
        {
            observers.erase(std::remove(observers.begin(), observers.end(), &observer),
                            observers.end());
        }

    private:
        std::vector<Observer<T>*>  observers;
};

template <class T>
struct Observable2
{
    signal<void(T&, const std::string&)> field_changed;
};

#endif
