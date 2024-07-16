add_requires("vcpkg::magic-enum", { debug = is_mode_debug(), configs = {baseline = "7aeffc91033ad35cc4e2c152f213a866ec6c11ac", runtimes = get_mode_runtimes()} })
add_requires("vcpkg::boost-nowide", { debug = is_mode_debug(), configs = {baseline = "7aeffc91033ad35cc4e2c152f213a866ec6c11ac", runtimes = get_mode_runtimes()} })
add_requires("vcpkg::boost-algorithm", { debug = is_mode_debug(), configs = {baseline = "7aeffc91033ad35cc4e2c152f213a866ec6c11ac", runtimes = get_mode_runtimes()} })
add_requires("vcpkg::boost-heap", { debug = is_mode_debug(), configs = {baseline = "7aeffc91033ad35cc4e2c152f213a866ec6c11ac", runtimes = get_mode_runtimes()} })
add_requires("vcpkg::plf-colony", { debug = is_mode_debug(), configs = {baseline = "7aeffc91033ad35cc4e2c152f213a866ec6c11ac", runtimes = get_mode_runtimes()} })
add_requires("vcpkg::boost-preprocessor", { debug = is_mode_debug(), configs = {baseline = "7aeffc91033ad35cc4e2c152f213a866ec6c11ac", runtimes = get_mode_runtimes()} })

local projectName = "WSystemCore"

target(projectName)
    add_rules("ue4ss.mod")

    add_packages("vcpkg::magic-enum")
    add_packages("vcpkg::boost-nowide")
    add_packages("vcpkg::boost-algorithm")
    add_packages("vcpkg::boost-heap")
    add_packages("vcpkg::plf-colony")
    add_packages("vcpkg::boost-preprocessor")

    add_includedirs(".")
    add_includedirs("./ThirdParty")
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