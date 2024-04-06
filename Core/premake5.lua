project "Core"
   kind "StaticLib"
   language "C++"
   cppdialect "C++20"
   targetdir "Binaries/%{cfg.buildcfg}"
   staticruntime "off"

   files { "Source/**.h", "Source/**.cpp" }

   includedirs
   {
      "Source",

      "../vendor/imgui",
      "../vendor/glfw/include",

      "%{IncludeDir.VulkanSDK}",
      "C:/opencv/build/include",
   }
   libdirs 
   {
       "C:/opencv/build/x64/vc16/lib"
   }
   links
   {
       "ImGui",
       "GLFW",

       "%{Library.Vulkan}"
   }

   targetdir ("../Binaries/" .. OutputDir .. "/%{prj.name}")
   objdir ("../Binaries/Intermediates/" .. OutputDir .. "/%{prj.name}")

   filter "system:windows"
       systemversion "latest"
       defines { }

   filter "configurations:Debug"
       defines { "DEBUG" }
       runtime "Debug"
       symbols "On"
       links
       { 
            "opencv_world490d"
       }

   filter "configurations:Release"
       defines { "RELEASE" }
       runtime "Release"
       optimize "On"
       symbols "On"
       links
       {
            "opencv_world490"
       }