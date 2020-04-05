#ifndef SAFER_OBSERVABLE_HPP
#define SAFER_OBSERVABLE_HPP

#include <string>
#include <vector>
#include <algorithm>
#include <mutex>

template <typename> struct Observer;

template <class T>
class SaferObservable
{
    private:
        using lock_t = std::scoped_lock<std::recursive_mutex>;

    public:
        void notify(T& source, const std::string& field_name)
        {
            lock_t lock { mutex_ };

            for(auto* observer : observers)
            {
                observer->field_changed(source, field_name);
            }
        }

        void subscribe(Observer<T>& observer)
        {
            lock_t lock { mutex_ };

            observers.push_back(&observer);
        }

        void unsubscribe(Observer<T>& observer)
        {
            lock_t lock { mutex_ };

            observers.erase(std::remove(observers.begin(), observers.end(), &observer),
                            observers.end());
        }

    private:
        std::vector<Observer<T>*>  observers;
        // Using a recursive_mutex here would fix the particular
        // issue with reentrancy, but it's not a popular option
        std::recursive_mutex mutex_;
};

#endif
