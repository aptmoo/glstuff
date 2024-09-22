#ifndef CONTEXT_H
#define CONTEXT_H
#include "types.h"

class GraphicsContext
{
public:
    GraphicsContext(void* handle);
    ~GraphicsContext();

    void Init();
    void Swap();

    void SetViewportSize(Size2D size);
    void SetViewportSize(VieportSize size);

private:
    void* m_pWindowHandle;
};

#endif