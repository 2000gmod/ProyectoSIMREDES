cmake_minimum_required(VERSION 3.20)

project(SimRedesProyecto)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(json DOWNLOAD_EXTRACT_TIMESTAMP true URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz)
FetchContent_MakeAvailable(json)


add_compile_options(-Wall -Wextra -Wpedantic)
add_compile_options(-Wno-unused-but-set-variable)

add_custom_target(config ALL
    COMMAND ${CMAKE_COMMAND} -E remove ${CMAKE_CURRENT_BINARY_DIR}/config.json
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/config.json ${CMAKE_CURRENT_BINARY_DIR}/config.json
    DEPENDS ${MY_TARGET}
)

set(sources
    src/Main.cpp
    src/Vec2.cpp
    src/Obstacle.cpp
    src/Simulator.cpp
    src/Scanner.cpp
    src/Parser.cpp
)

add_executable(lwsim ${sources})

target_link_libraries(lwsim PRIVATE nlohmann_json::nlohmann_json)