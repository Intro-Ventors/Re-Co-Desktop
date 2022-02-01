workspace "Scipper"
	architecture "x64"

	configurations {
		"Debug",
		"Release"
	}

	-- Setup the dependencies.
	IncludeDirectories = {}
	IncludeDirectories["screen_capture_lite"] = "%{wks.location}/ThirdParty/screen_capture_lite/include"
	IncludeDirectories["pybind11"] = "%{wks.location}/ThirdParty/pybind11/include"

	LibraryDirectories = {}
	LibraryDirectories["screen_capture_lite"] = "%{wks.location}/ThirdParty/screen_capture_lite/src_cpp/Release"

	Binaries = {}
	Binaries["screen_capture_lite"] = "screen_capture_lite_shared"

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

	-- Include the projects.
	include "Code/Scipper.lua"
	include "Test/Test.lua"
