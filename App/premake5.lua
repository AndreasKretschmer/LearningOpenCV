project "App"
   kind "ConsoleApp"
   language "C++"
   cppdialect "C++20"
   targetdir "Binaries/%{cfg.buildcfg}"
   staticruntime "off"

   files { "Source/**.h", "Source/**.cpp" }
   
   includedirs
   {
      "Source",

	  "../Core/Source",
      "C:/opencv/build/include",
      "../vendor/imgui",
      "%{IncludeDir.VulkanSDK}"
   }
   libdirs 
   {
       "C:/opencv/build/x64/vc16/lib"
   }
   links
   {
      "Core"
   }

   targetdir ("../Binaries/" .. OutputDir .. "/%{prj.name}")
   objdir ("../Binaries/Intermediates/" .. OutputDir .. "/%{prj.name}")

   filter "system:windows"
       systemversion "latest"
       defines { "WINDOWS" }

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