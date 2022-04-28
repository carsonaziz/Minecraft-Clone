workspace "Minecraft-Clone"
    startproject "minecraft"
    configurations { "Debug", "Release" }
    architecture "ARM64"

tdir = "bin/%{cfg.buildcfg}/%{cfg.system}"
odir = "bin-int/%{cfg.buildcfg}/%{cfg.system}"

-- External Dependencies --
dependencies = {}
dependencies["spdlog"] = "deps/spdlog"
dependencies["stb"] = "deps/stb"
dependencies["yamlcpp"] = "deps/yaml-cpp"
dependencies["glm"] = "deps/glm"
dependencies["glfw"] = "deps/glfw"
dependencies["glad"] = "deps/glad"

-- Build other libraries
include "deps/yaml-cpp"
include "deps/glad"

project "minecraft"
    location "minecraft"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"

    targetdir(tdir)
    objdir(odir)

    files
    {
        "%{prj.name}/include/**.h",
        "%{prj.name}/src/**.cpp",
    }

    sysincludedirs
    {
        "%{prj.name}/include",
        "%{dependencies.spdlog}/include",
        "%{dependencies.stb}",
        "%{dependencies.yamlcpp}/include",
        "%{dependencies.glm}",
        "%{dependencies.glfw}/include",
        "%{dependencies.glad}/include",
    }

    links { "glfw3", "glad", "yaml-cpp"}

    filter { "system:windows"}
        systemversion "latest"

        defines
        {
            "MINECRAFT_PLATFORM_WINDOWS"
        }

    filter { "system:macosx", "architecture:ARM64"}
        defines
        {
            "MINECRAFT_PLATFORM_MAC"
        }

        libdirs 
        {
            "%{dependencies.glfw}/lib-arm64"
        }

        links { "Cocoa.framework", "OpenGL.framework", "IOKit.framework" }
    
    filter { "system:macosx", "architecture:x86_64"}
        defines
        {
            "MINECRAFT_PLATFORM_MAC"
        }

        libdirs 
        {
            "%{dependencies.glfw}/lib-x86_64"
        }

        links { "Cocoa.framework", "OpenGL.framework", "IOKit.framework" }

    filter { "configurations:Debug" }
        defines
        {
            "MINECRAFT_CONFIG_DEBUG"
        }
        runtime "Debug"
        symbols "on"
        
    filter { "configurations:Release" }
        defines
        {
            "MINECRAFT_CONFIG_RELEASE"
        }
        runtime "Release"
        symbols "off"
        optimize "on"