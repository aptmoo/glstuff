project "tinyobjloader"
    kind "StaticLib"
    language "C++"
    cppdialect "C++11"
    targetname "tinyobjloader"
    targetdir "lib/"
    objdir "bin-int/"

    files
    {
        "ext/tinyobjloader/tiny_obj_loader.hh",
        "ext/tinyobjloader/tiny_obj_loader.cc",
    }

    includedirs
    {
        "ext/tinyobjloader",
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