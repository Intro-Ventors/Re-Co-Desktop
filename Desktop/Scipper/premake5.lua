workspace "Scipper"
	architecture "x64"

	configurations {
		"Debug",
		"Release"
	}

	filter "configurations:Debug"
		defines { "SCIPPER_DEBUG" }
		symbols "On"
		runtime "Debug"

	filter "configurations:Release"
		defines { "SCIPPER_RELEASE" }
		optimize "On"
		runtime "Release"

	filter "system:windows"
		defines { "SCIPPER_PLATFORM_WINDOWS" }

	filter "system:linux"
		defines { "SCIPPER_PLATFORM_LINUX" }

	filter ""

	-- Setup the dependencies.
	IncludeDirectories = {}
	IncludeDirectories["screen_capture_lite"] = "ThirdParty/screen_capture_lite/include"
	IncludeDirectories["pybind11"] = "ThirdParty/pybind11/include"

	LibraryDirectories = {}
	Binaries = {}

	-- Include the projects.
	include "Code/Scipper.lua"
	include "Test/Test.lua"
