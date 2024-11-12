#ifndef UNIFORMBUFFER_H
#define UNIFORMBUFFER_H
#include <string>
#include "layout.h"
#include "shader.h"
#include "types.h"

class UniformBuffer
{
public:
    UniformBuffer(const std::string& name, const GPUDataLayout& layout);
    ~UniformBuffer();

    /* TODO: Cache prop offsets */
    template<typename T>
    void SetProperty(const std::string& property, T& v) { static_assert(0); }

    unsigned int GetID() { return m_glID; }
    unsigned int GetID() const { return m_glID; }

    const std::string& GetName() { return m_Name; }
    const std::string& GetName() const { return m_Name; }
private:
    std::string m_Name;

    GPUDataLayout m_Layout;
    void* m_Data;

    unsigned int m_glID;
};

#endif