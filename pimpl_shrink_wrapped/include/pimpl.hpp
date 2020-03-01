#ifndef PIMPL_HPP
#define PIMPL_HPP

#include <memory>

template <typename T>
class pimpl
{
    public:
        pimpl() : impl { new T {} }
        {}
        ~pimpl() = default;

        template <typename ...Args>
        pimpl(Args&& ...args)
            : impl { new T { std::forward<Args>(args)... } }
        {}

        T* operator->()
        {
            return impl.get();
        }

        T& operator*()
        {
            return *impl.get();
        }

    private:
        std::unique_ptr<T> impl;
};

#endif
