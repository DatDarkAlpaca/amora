project "amora"
    kind "StaticLib"
    language "C++"
    cppdialect "C++20"

    targetdir(binaries_path .. "/%{prj.name}")
    objdir(intermediate_path .. "/%{prj.name}")

    files {
        "**.cpp",
        "**.hpp",
        "**.h",
    }
   
    includedirs {
        "%{prj.location}",
        "%{prj.location}/src"
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
