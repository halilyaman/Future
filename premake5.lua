workspace "Future"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

	startproject "Sandbox"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "Future/vendor/GLFW/include"
IncludeDir["Glad"] = "Future/vendor/Glad/include"
IncludeDir["ImGui"] = "Future/vendor/imgui"
IncludeDir["glm"] = "Future/vendor/glm"



group "Dependencies"
	include "Future/vendor/GLFW"
	include "Future/vendor/Glad"
	include "Future/vendor/imgui"

group ""

project "Future"
	location "Future"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "ftpch.h"
	pchsource "Future/src/ftpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl",
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}"
	}

	links
	{
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"FT_PLATFORM_WINDOWS",
			"FT_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

	filter "configurations:Debug"
		defines "FT_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "FT_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "FT_DIST"
		runtime "Release"
		symbols "on"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"Future/vendor/spdlog/include",
		"Future/src",
		"Future/vendor",
		"%{IncludeDir.glm}"
	}

	links
	{
		"Future"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"FT_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "FT_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "FT_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "FT_DIST"
		runtime "Release"
		symbols "on"