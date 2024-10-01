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
        _NONE = -1, VERTEX=0, FRAGMENT=1,
    } type = StageType::_NONE;

    std::string path = m_ContentDir + name + ".shd";
    std::ifstream file(path);
    std::string line;
    std::stringstream streams[2];

    while (getline(file, line))
    {
        if(line.find("@shader") != std::string::npos)
        {
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

    vs_source = streams[0].str();
    fs_source = streams[1].str();

    m_Shaders.emplace(name, MakeRef<Shader>(vs_source, fs_source));
    return m_Shaders.at(name);
}