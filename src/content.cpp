#include "content.h"
#include <fstream>
#include <sstream>


#include <iostream>
template<>
Ref<Shader> ContentManager::Load(const std::string& name)
{
    if(m_Shaders.find(name) != m_Shaders.end())
    {
        return m_Shaders.at(name);
    }

    std::string vs_source, fs_source;
    enum class StageType
    {
        _NONE = -1, SHARED, VERTEX=1, FRAGMENT=2, COUNT
    } type = StageType::_NONE;

    std::string path = m_ContentDir + name + ".shd";
    std::ifstream file(path);
    std::string line;
    std::stringstream streams[(int)StageType::COUNT];

    while (getline(file, line))
    {
        if(line.find("@shader") != std::string::npos)
        {
            if(line.find("shared") != std::string::npos)
                type = StageType::SHARED;
            if(line.find("vertex") != std::string::npos)
                type = StageType::VERTEX;
            if(line.find("fragment") != std::string::npos)
                type = StageType::FRAGMENT;
        }
        else
        {
            if(type != StageType::_NONE)
                streams[(int)type] << line << '\n';
        }
    }

    vs_source = streams[(int)StageType::SHARED].str() + streams[(int)StageType::VERTEX].str();
    fs_source = streams[(int)StageType::SHARED].str() + streams[(int)StageType::FRAGMENT].str();

    m_Shaders.emplace(name, MakeRef<Shader>(vs_source, fs_source));
    return m_Shaders.at(name);
}