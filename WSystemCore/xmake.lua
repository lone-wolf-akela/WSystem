add_requires("vcpkg::magic-enum", { debug = is_mode_debug(), configs = {baseline = "3508985146f1b1d248c67ead13f8f54be5b4f5da", runtimes = get_mode_runtimes()} })
add_requires("vcpkg::boost-nowide", { debug = is_mode_debug(), configs = {baseline = "3508985146f1b1d248c67ead13f8f54be5b4f5da", runtimes = get_mode_runtimes()} })
add_requires("vcpkg::boost-algorithm", { debug = is_mode_debug(), configs = {baseline = "3508985146f1b1d248c67ead13f8f54be5b4f5da", runtimes = get_mode_runtimes()} })
add_requires("vcpkg::boost-preprocessor", { debug = is_mode_debug(), configs = {baseline = "3508985146f1b1d248c67ead13f8f54be5b4f5da", runtimes = get_mode_runtimes()} })

local projectName = "WSystemCore"

target(projectName)
    add_rules("ue4ss.mod")

    add_packages("vcpkg::magic-enum")
    add_packages("vcpkg::boost-nowide")
    add_packages("vcpkg::boost-algorithm")
    add_packages("vcpkg::boost-preprocessor")

    add_includedirs(".")
    add_includedirs("./ThirdParty")

    set_pcxxheader("pch.h")
    add_headerfiles("pch.h")

    add_files("dllmain.cpp")
    add_files("utils.cpp")
    add_headerfiles("utils.h")
    add_headerfiles("ThirdParty/UnrealContainers/UnrealContainers.h")
    add_headerfiles("ThirdParty/sol/*.hpp")

    add_headerfiles("DataWrapper/*.h")
    add_files("DataWrapper/*.cpp")

    add_headerfiles("LibWrapper/*.h")
    add_files("LibWrapper/*.cpp")

    add_headerfiles("Core/*.h")
    add_files("Core/*.cpp")

    add_headerfiles("LuaInterface/*.h")
    add_files("LuaInterface/*.cpp")