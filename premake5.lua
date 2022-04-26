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

-- Build other libraries
include "deps/yaml-cpp"

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
    }

    libdirs 
    {

    }

    links {"yaml-cpp"}

    filter { "system:windows"}
        systemversion "latest"

        defines
        {
            "MINECRAFT_PLATFORM_WINDOWS"
        }

    filter { "system:macosx"}
        defines
        {
            "MINECRAFT_PLATFORM_MAC"
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