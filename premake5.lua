workspace "raycaster"
	toolset "clang"

	configurations {"Debug", "Release"}

	prebuildcommands {
		"mkdir -p %{cfg.buildtarget.directory}",
		"cp -r assets %{cfg.buildtarget.directory}",
	}

project "raycaster"
	kind "ConsoleApp"
	language "C"
	cdialect "C11"
	targetdir "bin/%{cfg.buildcfg}"

	includedirs {
		"include",
		"third_party/glad/include",
		"third_party/cglm/include",
	}

	buildoptions {
		"`pkg-config --cflags glfw3`"
	}

	linkoptions {
		"`pkg-config --libs glfw3`"
	}

	files {
		"src/**.h",
		"src/**.c",
		"third_party/cglm/src/**.c",
	}

	filter "configurations:Debug"
		defines { "DEBUG" }
		symbols "On"

	filter "configurations:Release"
		defines { "NDEBUG" }
		optimize "On"
