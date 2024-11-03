project "stb"
    kind "StaticLib"
    language "C"
    targetname "stb"
    targetdir "lib/"
    objdir "bin-int/"

    files
    {
        "ext/stb/**.h",
        "ext/stb/**.c",
    }

    includedirs
    {
        "ext/stb",
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
        links { "dl", "m", "pthread",}
        libdirs { "/lib/", "/usr/lib" }
    
    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"
  
     filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"