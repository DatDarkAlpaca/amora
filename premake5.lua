require "scripts/clear"
include "dependencies/conandeps.premake5.lua"

workspace "amora"
    architecture "x64"
    configurations {
        "Debug",
        "Release"
    }

    startproject "amora-game"

output_path         = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
binaries_path       = "%{wks.location}/build/bin/" .. "%{output_path}"
intermediate_path   = "%{wks.location}/build/intermediate/" .. "%{output_path}"

include "amora/amora_build.lua"
include "amora-game/amora_game_build.lua"