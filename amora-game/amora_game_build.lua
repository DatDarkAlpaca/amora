project "amora-game"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++20"

    targetdir(binaries_path .. "/%{prj.name}")
    objdir(intermediate_path .. "/%{prj.name}")

    links {
        "amora"
    }

    files {
        "src/**.cpp",
        "src/**.hpp",
        "src/**.h"
    }
    
    includedirs {
        "%{prj.location}",
        "%{prj.location}/src",
        "%{wks.location}/amora/",
        "%{wks.location}/amora/src",
    }

    -- Configurations
    filter { "configurations:Debug" }
        runtime "Debug"
        symbols "on"
    filter { }
        
    filter { "configurations:Release" }
        runtime "Release"
        optimize "on"
        inlining "auto"
    filter { }

    conan_setup()
