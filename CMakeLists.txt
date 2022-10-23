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
    ${CMAKE_CURRENT_LIST_DIR}/datamanager/nidm.hpp
)

target_include_directories(nidm PUBLIC 
    ${CMAKE_CURRENT_LIST_DIR}/framework/
)


add_executable(nigf_demo)

target_sources(nigf_demo PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/test_main.cpp
    ${CMAKE_CURRENT_LIST_DIR}/renderer.cpp
    ${CMAKE_CURRENT_LIST_DIR}/renderer.hpp
    ${CMAKE_CURRENT_LIST_DIR}/player.cpp
    ${CMAKE_CURRENT_LIST_DIR}/player.hpp
)

target_include_directories(nigf_demo PUBLIC 
    ${CMAKE_CURRENT_LIST_DIR}/framework/
    ${CMAKE_CURRENT_LIST_DIR}/datamanager/
)

target_link_libraries(nigf_demo PUBLIC
    nigf
    nidm
)


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
