project "glad"
    kind "StaticLib"
    language "C"
    targetname "GLFW"
    targetdir "lib/"
    objdir "bin-int/"

    files
    {
        "ext/glad/include/**.h",
        "ext/glad/src/**.h",
        "ext/glad/src/**.c",
    }

    includedirs
    {
        "ext/glad/include/",
    }

    libdirs
    {
        "lib/"
    }

    links
    {
        
    }

    filter "system:linux"
        defines { "SYSTEM_LINUX" }
        links { "dl", "m", "pthread", "GL" }
        libdirs { "/lib/", "/usr/lib" }
    
    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"
  
     filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"