#ifndef WINDOW_H
#define WINDOW_H
#include <string>
#include "types.h"

struct WindowDesc
{
    int Width, Height;
    std::string Title;
};

struct WindowData
{
    int Width, Height;
    bool SizeChanged;
};

class Window
{
public:
    Window(const WindowDesc& desc);
    ~Window();

    void OnUpdate();

    int GetWidth()        { return m_Desc.Width;       }
    int GetHeight()       { return m_Desc.Height;      }
    bool GetSizeChanged() { return m_Desc.SizeChanged; }

    Size2D GetSize() { return {m_Desc.Width, m_Desc.Height}; }

    void* GetHandle() { return m_pWindowHandle; }

    bool ShouldClose();
private:    
    WindowData m_Desc;
    void* m_pWindowHandle;
};

#endif