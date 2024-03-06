cmake_minimum_required(VERSION "3.11")
include(FetchContent)

project(Pacman)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${Pacman_SOURCE_DIR}/bin")

set(SFML_VERSION "2.5.1")   
set(FETCHCONTENT_QUIET OFF)

# Create a header with absolute path to data
set(ASSETS_DIR "\"${CMAKE_CURRENT_SOURCE_DIR}/assets/\"")
set(DATA_DIR "\"${CMAKE_CURRENT_SOURCE_DIR}/data/\"")
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/include/Config/DataConfig.h.in ${CMAKE_CURRENT_SOURCE_DIR}/include/Config/DataConfig.h)

# Variables to all source files
set (
    SOURCE_UI
    ${Pacman_SOURCE_DIR}/src/UI/UI.cpp
    ${Pacman_SOURCE_DIR}/src/UI/Container.cpp
    ${Pacman_SOURCE_DIR}/src/UI/RemoveContainer.cpp
    ${Pacman_SOURCE_DIR}/src/UI/Label.cpp
    ${Pacman_SOURCE_DIR}/src/UI/Button.cpp
    ${Pacman_SOURCE_DIR}/src/UI/GameUI.cpp
    ${Pacman_SOURCE_DIR}/src/UI/Map.cpp
    ${Pacman_SOURCE_DIR}/src/UI/Table.cpp
)

set (
    SOURCE_ENTITY
    ${Pacman_SOURCE_DIR}/src/Entity/Entity.cpp
    ${Pacman_SOURCE_DIR}/src/Entity/Pacman.cpp
    ${Pacman_SOURCE_DIR}/src/Entity/Ghost.cpp
    ${Pacman_SOURCE_DIR}/src/Entity/GhostStrategy.cpp
    ${Pacman_SOURCE_DIR}/src/Entity/Movement.cpp
)

set (
    SOURCE_TOOLS
    ${Pacman_SOURCE_DIR}/src/Tools/General.cpp
    ${Pacman_SOURCE_DIR}/src/Tools/ResourceManager.cpp
    ${Pacman_SOURCE_DIR}/src/Tools/ObserverPattern.cpp
    ${Pacman_SOURCE_DIR}/src/Tools/Timer.cpp
    ${Pacman_SOURCE_DIR}/src/Tools/DataManager.cpp
)

set (
    SOURCE_COLLEC
    ${Pacman_SOURCE_DIR}/src/Collectable/Collectable.cpp
    ${Pacman_SOURCE_DIR}/src/Collectable/Food.cpp
    ${Pacman_SOURCE_DIR}/src/Collectable/PowerUp.cpp
)

set (
    SOURCE_SCENES
    ${Pacman_SOURCE_DIR}/src/Scenes/Menu.cpp
    ${Pacman_SOURCE_DIR}/src/Scenes/GameScene.cpp
    ${Pacman_SOURCE_DIR}/src/Scenes/Lost.cpp
    ${Pacman_SOURCE_DIR}/src/Scenes/ScoreTable.cpp
)

set (
    SOURCE_MAP
    ${Pacman_SOURCE_DIR}/src/Map/Field.cpp   
    ${Pacman_SOURCE_DIR}/src/Map/Level.cpp
    ${Pacman_SOURCE_DIR}/src/Map/Game.cpp
)

set(SOURCE
    ${SOURCE_ENTITY}
    ${SOURCE_MAP}
    ${SOURCE_SCENES}
    ${SOURCE_COLLEC}
    ${SOURCE_TOOLS}
    ${SOURCE_UI}
)

# Download json-library
FetchContent_Declare(
    json
    URL https://github.com/nlohmann/json/releases/download/v3.11.2/json.tar.xz
)
FetchContent_MakeAvailable(json)

# Create folder to store user's data
file(MAKE_DIRECTORY "data")

# Download SFML-library

# SFML library depends on many others
# On Windows and macOS, all the required dependencies are provided alongside SFML
# But not on UNIX systems, so it is much easier to download it using package manager
# In this case, it will work only on Debian systems
if (UNIX)
    find_program(PACKAGE_MANAGER apt-get)
    execute_process (
        COMMAND ${PACKAGE_MANAGER} install libsfml-dev
    )
    find_package(SFML COMPONENTS system window graphics network audio REQUIRED)
else()
    FetchContent_Declare(
        sfml
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG "${SFML_VERSION}"
    )
    FetchContent_MakeAvailable(sfml)
endif (UNIX)

add_executable(Pacman ${Pacman_SOURCE_DIR}/main.cpp ${SOURCE})

target_link_libraries(Pacman sfml-graphics sfml-audio sfml-window sfml-system)
target_link_libraries(Pacman nlohmann_json::nlohmann_json)

target_include_directories(Pacman PRIVATE ${Pacman_SOURCE_DIR}/include/Tools)
target_include_directories(Pacman PRIVATE ${Pacman_SOURCE_DIR}/include/Config)
target_include_directories(Pacman PRIVATE ${Pacman_SOURCE_DIR}/include/UI)
target_include_directories(Pacman PRIVATE ${Pacman_SOURCE_DIR}/include/Entity)
target_include_directories(Pacman PRIVATE ${Pacman_SOURCE_DIR}/include/Map)
target_include_directories(Pacman PRIVATE ${Pacman_SOURCE_DIR}/include/Collectable)
target_include_directories(Pacman PRIVATE ${Pacman_SOURCE_DIR}/include/Scenes)
target_include_directories(Pacman PRIVATE ${Pacman_SOURCE_DIR}/include)