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

add_executable(main src/main.cpp "src/game.h" "src/game.cpp" "src/gameobject.h" "src/gameobject.cpp" "src/rigidbody.h" "src/rigidbody.cpp" "src/boid/boid.h" "src/boid/boid.cpp" "src/component.h" "src/component.cpp" "src/renderable.h" "src/boid/boid.h" "src/renderable.cpp" "src/steeringoutput.h" "src/steeringoutput.cpp" "src/steeringbehavior.h" "src/steeringbehavior.cpp")
target_compile_features(main PRIVATE cxx_std_17)
target_link_libraries(main PRIVATE SFML::Graphics)
target_include_directories(main PRIVATE ${CMAKE_SOURCE_DIR}/src)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT main)