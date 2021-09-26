workspace "bfc"
    configurations { "debug", "release" }

project "bfc"
    kind "ConsoleApp"
    language "C"
    location "bin"
    targetdir "bin/%{cfg.buildcfg}"

    files { "**.h", "**.c" }
    includedirs { "src/include" }

    links { "readline" }

    filter "configurations:debug"
        defines { "DEBUG" }
        symbols "On"

    filter "configurations:release"
        optimize "Full"

    newaction {
        trigger     = "clean",
        description = "clean the project",
        execute     = function ()
            os.rmdir("./bin")
            os.remove("Makefile")
        end
    }