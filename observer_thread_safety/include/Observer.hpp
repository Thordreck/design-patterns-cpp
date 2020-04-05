#ifndef OBSERVER_HPP
#define OBSERVER_HPP

#include <string>

template <class T>
struct Observer
{
    virtual void field_changed(T& source, const std::string& field_name) = 0;
};

#endif
