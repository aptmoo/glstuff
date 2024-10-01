#ifndef CONTENT_H
#define CONTENT_H
#include <unordered_map>
#include "types.h"
#include "shader.h"

class ContentManager
{
public:
    ContentManager(const std::string& dir = "")
        : m_ContentDir(dir) {};
    ~ContentManager(){};

    template<typename T>
    Ref<T> Load(const std::string& name) { static_assert(0); }
private:
    std::string m_ContentDir;
    std::unordered_map<std::string, Ref<Shader>> m_Shaders;
};

template<>
Ref<Shader> ContentManager::Load(const std::string& name);


#endif