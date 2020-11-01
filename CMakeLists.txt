cmake_minimum_required(VERSION 3.16)
project(CppBoilerplate)

set(CMAKE_CXX_STANDARD 17)

option(BUILD_oglBoilerplate "Build openGL Demo" ON)
option(BUILD_pythonEmbed "Build embed python Demo" OFF)

if (WIN32)
    add_definitions(-DUNICODE -D_UNICODE)
    add_definitions(-DWIN32_LEAN_AND_MEAN)

    foreach (flag_var CMAKE_CXX_FLAGS CMAKE_CXX_FLAGS_DEBUG CMAKE_CXX_FLAGS_RELEASE CMAKE_CXX_FLAGS_MINSIZEREL CMAKE_CXX_FLAGS_RELWITHDEBINFO)
        if (${flag_var} MATCHES "/MD")
            string(REGEX REPLACE "/MD" "/MT" ${flag_var} "${${flag_var}}")
        endif()
    endforeach()

    add_compile_options("/MP")
endif()

if (UNIX)
    add_definitions(-DUNIX)
    add_compile_options("-Wall")
    add_compile_options("-fvisibility=hidden")

    find_package(Backtrace REQUIRED)
    set(extra_libs -lbacktrace -lstdc++fs -ldl)
endif ()

find_package(glfw3 REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)
find_package(stb REQUIRED)
find_package(tinyobjloader CONFIG REQUIRED)

include_directories(${glfw3_INCLUDE_DIRS})
include_directories(${glm_INCLUDE_DIRS})
include_directories(${imgui_INCLUDE_DIRS})
include_directories(${stb_INCLUDE_DIRS})
include_directories(${tinyobjloader_INCLUDE_DIRS})

# IMGUI EXAMPLE AND GLAD
include_directories(3rd_party/imgui)
set(src_files_imgui
        3rd_party/imgui/imgui_impl_glfw.cpp
        3rd_party/imgui/imgui_impl_glfw.h
        3rd_party/imgui/imgui_impl_opengl3.cpp
        3rd_party/imgui/imgui_impl_opengl3.h)

include_directories(3rd_party/glad/include)
set(src_files_glad
        3rd_party/glad/src/glad.c)

# EXE
if(BUILD_oglBoilerplate)
    set(exe_name oglBoilerplate)
    add_executable(${exe_name} main.cpp ${src_files_imgui} ${src_files_glad})
    target_link_libraries(${exe_name} PRIVATE glfw glm imgui::imgui  ${extra_libs})
endif(BUILD_oglBoilerplate)

if(BUILD_pythonEmbed)
    #  vcpkg.exe install pybind11:x64-windows
    #  vcpkg.exe install pybind11:x64-windows-static
#    find_package(pybind11 CONFIG REQUIRED)
#    target_link_libraries(main PRIVATE mylib pybind11::embed pybind11::module pybind11::pybind11)

    find_package(pybind11 CONFIG REQUIRED)
    include_directories(${pybind11_INCLUDE_DIRS})

    set(exe2_name pythonEmbed)
    add_executable(${exe2_name} pybind11.cpp)
    target_link_libraries(${exe2_name} PRIVATE pybind11::embed)
endif()
