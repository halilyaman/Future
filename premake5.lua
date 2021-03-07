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
	kind "SharedLib"
	language "C++"
	staticruntime "off"

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
		cppdialect "C++17"
		systemversion "latest"

		defines
		{
			"FT_PLATFORM_WINDOWS",
			"FT_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/Sandbox/\"")
		}

	filter "configurations:Debug"
		defines "FT_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "FT_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "FT_DIST"
		runtime "Release"
		symbols "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	staticruntime "off"

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
		"%{IncludeDir.glm}"
	}

	links
	{
		"Future"
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines
		{
			"FT_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "FT_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "FT_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "FT_DIST"
		runtime "Release"
		symbols "On"