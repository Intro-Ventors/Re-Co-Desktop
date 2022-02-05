project "Test"
	kind "ConsoleApp"
	cppdialect "C++20"
	language "C++"
	systemversion "latest"
	staticruntime "on"

	flags { "MultiProcessorCompile" }

	targetdir "%{wks.location}/Builds/%{cfg.longname}"
	objdir "%{wks.location}/Builds/Intermediate/%{cfg.longname}"

	files {
		"**.txt",
		"**.cpp",
		"**.hpp",
		"**.h",
		"**.lua",
	}

	includedirs {
		"%{wks.location}/Code",
		"%{wks.location}/Tests",
	}

	libdirs {
	}

	links {
		"Scipper",
	}

	filter { "toolset:msc", "configurations:Debug" }
	    buildoptions "/MTd"

	filter { "toolset:msc", "configurations:Release" }
	    buildoptions "/MT"

	filter ""