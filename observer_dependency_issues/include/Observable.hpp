#ifndef OBSERVABLE_HPP
#define OBSERVABLE_HPP

#include <string>
#include <vector>
#include <algorithm>

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

#endif
