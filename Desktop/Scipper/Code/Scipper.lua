project "Scipper"
	language "C++"
	kind "SharedLib"
	systemversion "latest"
	cppdialect "C++20"
	staticruntime "on"

	flags { "MultiProcessorCompile" }

	targetdir "%{wks.location}/Builds/%{cfg.longname}"
	objdir "%{wks.location}/Builds/%{cfg.longname}"

	files {
		"**.txt",
		"**.cpp",
		"**.hpp",
		"**.lua",
		"**.txt",
		"**.md",
	}

	includedirs {
		"%{wks.location}/Code/",
		"%{IncludeDirectories.screen_capture_lite}",
	}
	
	libdirs {
		"%{LibraryDirectories.screen_capture_lite}",
	}
	
	links { 
		"%{Binaries.screen_capture_lite}",
	}

	filter { "toolset:msc", "configurations:Debug" }
	    buildoptions "/MTd"

	filter { "toolset:msc", "configurations:Release" }
	    buildoptions "/MT"

	filter ""