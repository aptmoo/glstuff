#ifndef TYPES_H
#define TYPES_H
#include <memory>

struct Size2D
{
    int width, height;
};

struct VieportSize
{
    int x, y;
    int width, height;
};

template<typename T>
using Ref = std::shared_ptr<T>;

template<typename T, typename ... TArgs>
Ref<T> MakeRef(TArgs&&... args)
{
    return std::make_shared<T>(std::forward<TArgs>(args)...);
}

template<typename T>
using Scope = std::unique_ptr<T>;

template<typename T, typename ... TArgs>
Scope<T> MakeScope(TArgs&&... args)
{
    return std::make_unique<T>(std::forward<TArgs>(args)...);
}

#endif