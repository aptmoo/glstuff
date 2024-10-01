project "Application"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    targetname "App"
    targetdir "bin/"
    objdir "bin-int/"

    files
    {
        "src/**.h",
        "src/**.cpp",
    }

    includedirs
    {
        "src/",

        "ext/glad/include/",
        "ext/glfw/include",
        "ext/stb/",
    }

    libdirs
    {
        "lib/"
    }

    links
    {
        "GLFW", "GL", "glad"
    }

    defines
    {
        "GLFW_INCLUDE_NONE"
    }

    filter "system:linux"
        targetsuffix ".out"
        defines { "SYSTEM_LINUX" }
        links { "dl", "m", "pthread", }
        libdirs { "/lib/", "/usr/lib" }
    
    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"
  
     filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"