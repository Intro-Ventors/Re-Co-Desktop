project "Scipper"
	language "C++"
	kind "StaticLib"
	systemversion "latest"
	cppdialect "C++20"
	staticruntime "on"

	flags { "MultiProcessorCompile" }

	targetdir "%{wks.location}/Builds/%{cfg.longname}"
	objdir "%{wks.location}/Builds/Intermediate/%{cfg.longname}"

	defines { "SCIPPER_SHARED" }

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
	    buildoptions "/MDd"

	filter { "toolset:msc", "configurations:Release" }
	    buildoptions "/MD"
