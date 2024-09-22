project "GLFW"
    kind "StaticLib"
    language "C"
    targetname "GLFW"
    targetdir "lib/"
    objdir "bin-int/"

    files
    {
        "ext/glfw/include/**.h",
        "ext/glfw/src/**.h",
        "ext/glfw/src/**.c",
    }

    includedirs
    {
        "ext/glfw/include/**.h",
    }

    libdirs
    {
        "lib/"
    }

    links
    {
        
    }

    filter "system:linux"
        defines { "SYSTEM_LINUX", "_GLFW_X11",} -- "_GLFW_WAYLAND" }
        links { "dl", "m", "pthread" }
        libdirs { "/lib/", "/usr/lib" }
    
    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"
  
     filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"