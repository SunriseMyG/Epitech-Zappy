cmake_minimum_required(VERSION 3.10)
project(zappy_gui)

set(CMAKE_CXX_STANDARD 17)

include_directories(gui)


add_executable(zappy_gui
main.cpp
Core/Core.cpp
Graphics/AObject.cpp
Graphics/AUI.cpp
Graphics/AUIText.cpp
Graphics/Text.cpp
Graphics/Sprite.cpp
Graphics/Object.cpp
Graphics/SoundManager.cpp
Graphics/MyCamera.cpp
Graphics/MyWindow.cpp
ServerClient/ServerClient.cpp
Core/MapTile.cpp
Core/Player.cpp
Core/Inventory.cpp
Core/Egg.cpp
Factory/FactoryObject.cpp
Factory/FactoryUI.cpp

)
target_link_libraries(zappy_gui PRIVATE raylib)

set_target_properties(zappy_gui PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/..
)