# CMakeList.txt : projet CMake pour Bataille Navale, incluez la source et définissez
# la logique spécifique au projet ici.
#
cmake_minimum_required(VERSION 3.14)

# Activez Rechargement à chaud pour les compilateurs MSVC si cela est pris en charge.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project(bataille-navale)

# raylib
find_package(raylib QUIET)
if (NOT raylib_FOUND)
    include(FetchContent)
    FetchContent_Declare(
        raylib
        GIT_REPOSITORY https://github.com/raysan5/raylib.git
        GIT_TAG 4.5.0
    )
    FetchContent_MakeAvailable(raylib)
endif()

# raylib-cpp
find_package(raylib_cpp QUIET)
if (NOT raylib_cpp_FOUND)
    include(FetchContent)
    FetchContent_Declare(
        raylib_cpp
        GIT_REPOSITORY https://github.com/RobLoach/raylib-cpp.git
        GIT_TAG v4.5.1
    )
    FetchContent_MakeAvailable(raylib_cpp)
endif()

find_package(easy-socket QUIET)
if (NOT easy-socket_FOUND)
    include(FetchContent)
    FetchContent_Declare(
        easy-socket
        GIT_REPOSITORY https://github.com/flufy3d/easy-socket.git
    )
    FetchContent_MakeAvailable(easy-socket)
endif()

# This is the main part:
add_executable(${PROJECT_NAME} "source/main.cpp" "source/boat.cpp" "source/visualgame.cpp" "source/textureasset.cpp" "include/visualgame.hpp" "source/internalgame.cpp" "source/consolegame.cpp")
target_include_directories(${PROJECT_NAME} PUBLIC "include")
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 11)
target_link_libraries(${PROJECT_NAME} PUBLIC glfw raylib raylib_cpp easy-socket)

# Web Configurations
if (${PLATFORM} STREQUAL "Web")
    # Tell Emscripten to build an example.html file.
    set_target_properties(${PROJECT_NAME} PROPERTIES SUFFIX ".html")

    # Required linker flags for using Raylib with Emscripten
    target_link_options(${PROJECT_NAME} PRIVATE -sEXPORTED_FUNCTIONS=['_main','_malloc'] -sEXPORTED_RUNTIME_METHODS=ccall -sUSE_GLFW=3)
endif()

# That's it! You should have an example executable that you can run. Have fun!