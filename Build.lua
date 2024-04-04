-- premake5.lua
workspace "LearningOpenCV"
   architecture "x64"
   configurations { "Debug", "Release" }
   startproject "App"

   -- Workspace-wide build options for MSVC
   filter "system:windows"
      buildoptions { "/EHsc", "/Zc:__cplusplus" }

OutputDir = "%{cfg.system}-%{cfg.architecture}/%{cfg.buildcfg}"

include "ExternalPremake.lua"
include "App"