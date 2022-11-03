cmake_minimum_required(VERSION 3.0.0)
project(nigf_demo VERSION 0.1.0)

include(CTest)
enable_testing()

add_library(nigf)

target_sources(nigf PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/framework/gameplay.cpp
    ${CMAKE_CURRENT_LIST_DIR}/framework/gameplay.hpp
    ${CMAKE_CURRENT_LIST_DIR}/framework/image.cpp
    ${CMAKE_CURRENT_LIST_DIR}/framework/image.hpp
    ${CMAKE_CURRENT_LIST_DIR}/framework/msgobject.cpp
    ${CMAKE_CURRENT_LIST_DIR}/framework/msgobject.hpp
    ${CMAKE_CURRENT_LIST_DIR}/framework/gamespirite.cpp
    ${CMAKE_CURRENT_LIST_DIR}/framework/gamespirite.hpp
    ${CMAKE_CURRENT_LIST_DIR}/framework/gameplay.cpp
    ${CMAKE_CURRENT_LIST_DIR}/framework/gameplay.hpp
    ${CMAKE_CURRENT_LIST_DIR}/framework/gameobject.cpp
    ${CMAKE_CURRENT_LIST_DIR}/framework/gameobject.hpp
    ${CMAKE_CURRENT_LIST_DIR}/framework/animation.cpp
    ${CMAKE_CURRENT_LIST_DIR}/framework/animation.hpp
    ${CMAKE_CURRENT_LIST_DIR}/framework/keyboard.cpp
    ${CMAKE_CURRENT_LIST_DIR}/framework/keyboard.hpp
    ${CMAKE_CURRENT_LIST_DIR}/framework/audio.cpp
    ${CMAKE_CURRENT_LIST_DIR}/framework/audio.hpp
)

target_include_directories(nigf PUBLIC 
    ${CMAKE_CURRENT_LIST_DIR}/3rdparty/
)

target_link_libraries(nigf PUBLIC
    GL
    glfw
)

add_library(nidm)

target_sources(nidm PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/datamanager/objmanager.hpp
    ${CMAKE_CURRENT_LIST_DIR}/datamanager/objmanager.cpp
    ${CMAKE_CURRENT_LIST_DIR}/datamanager/gomanager.hpp
    ${CMAKE_CURRENT_LIST_DIR}/datamanager/gomanager.cpp
    ${CMAKE_CURRENT_LIST_DIR}/datamanager/msgmanager.hpp
    ${CMAKE_CURRENT_LIST_DIR}/datamanager/msgmanager.cpp
    ${CMAKE_CURRENT_LIST_DIR}/datamanager/gsmanager.hpp
    ${CMAKE_CURRENT_LIST_DIR}/datamanager/gsmanager.cpp
    ${CMAKE_CURRENT_LIST_DIR}/datamanager/animanager.hpp
    ${CMAKE_CURRENT_LIST_DIR}/datamanager/animanager.cpp
    ${CMAKE_CURRENT_LIST_DIR}/datamanager/audiomanager.hpp
    ${CMAKE_CURRENT_LIST_DIR}/datamanager/audiomanager.cpp
    ${CMAKE_CURRENT_LIST_DIR}/datamanager/nidm.hpp
)

target_include_directories(nidm PUBLIC 
    ${CMAKE_CURRENT_LIST_DIR}/framework/
)

add_library(audioplayer)

target_sources(audioplayer PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/audioplayer/audioplayer.cpp
    ${CMAKE_CURRENT_LIST_DIR}/audioplayer/audioplayer.hpp
)

target_link_libraries(audioplayer PUBLIC openal)

add_library(render)

target_sources(render PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/render/renderer.cpp
    ${CMAKE_CURRENT_LIST_DIR}/render/renderer.hpp
)

target_include_directories(render PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/framework
)

add_executable(nigf_demo)

target_sources(nigf_demo PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/test_main.cpp
    ${CMAKE_CURRENT_LIST_DIR}/custom/player.hpp
    ${CMAKE_CURRENT_LIST_DIR}/custom/player.cpp
    ${CMAKE_CURRENT_LIST_DIR}/custom/background.hpp
    ${CMAKE_CURRENT_LIST_DIR}/custom/background.cpp
    ${CMAKE_CURRENT_LIST_DIR}/custom/sunflower.hpp
    ${CMAKE_CURRENT_LIST_DIR}/custom/sunflower.cpp
    ${CMAKE_CURRENT_LIST_DIR}/custom/dragon.hpp
    ${CMAKE_CURRENT_LIST_DIR}/custom/dragon.cpp
)

target_include_directories(nigf_demo PUBLIC 
    ${CMAKE_CURRENT_LIST_DIR}/framework/
    ${CMAKE_CURRENT_LIST_DIR}/datamanager/
    ${CMAKE_CURRENT_LIST_DIR}/render/
    ${CMAKE_CURRENT_LIST_DIR}/custom/
    ${CMAKE_CURRENT_LIST_DIR}/audioplayer/
)

target_link_libraries(nigf_demo PUBLIC
    nigf
    nidm
    render
    audioplayer
)


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
