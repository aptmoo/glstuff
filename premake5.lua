workspace "GLStuff"
    architecture "x86_64"

    configurations
    {
        "Debug",
        "Release" 
    }

include "glad.lua"
include "glfw.lua"
include "stb.lua"

include "application.lua"