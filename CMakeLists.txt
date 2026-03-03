cmake_minimum_required(VERSION 3.28)
project(CMakeSFMLProject LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.2
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

FetchContent_Declare(imgui
    GIT_REPOSITORY https://github.com/ocornut/imgui.git
    GIT_TAG 97428e8ac99e339ce05eee531cf55b77b29ea709
)
FetchContent_MakeAvailable(imgui)

FetchContent_Declare(ImGui-SFML
    GIT_REPOSITORY https://github.com/SFML/imgui-sfml.git
    GIT_TAG ab6b5cfeddb4eb980a42b526dc66901a0976ff6d
)

message(STATUS "Fetching ImGui-SFML...")

set(IMGUI_DIR ${imgui_SOURCE_DIR})
set(IMGUI_SFML_FIND_SFML OFF)
set(IMGUI_SFML_IMGUI_DEMO ON)

FetchContent_MakeAvailable(ImGui-SFML)

add_executable(main src/main.cpp "src/game.h" "src/game.cpp" "src/gameobject.h" "src/gameobject.cpp" "src/components/rigidbody.h" "src/components/rigidbody.cpp" "src/boid/boid.h" "src/boid/boid.cpp" "src/components/component.h" "src/components/component.cpp" "src/components/renderable.h" "src/boid/boid.h" "src/components/renderable.cpp" "src/steering/steeringoutput.h" "src/steering/steeringoutput.cpp" "src/steering/steeringbehavior.h"  "src/steering/seek.h" "src/steering/flee.cpp" "src/steering/flee.h" "src/steering/seek.cpp" )
target_compile_features(main PRIVATE cxx_std_17)
target_link_libraries(main PRIVATE ImGui-SFML::ImGui-SFML)
target_include_directories(main PRIVATE ${CMAKE_SOURCE_DIR}/src)
target_include_directories(main PRIVATE ${CMAKE_SOURCE_DIR}/imgui)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT main)