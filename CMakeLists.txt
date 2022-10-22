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
)

target_include_directories(nigf PUBLIC 
    ${CMAKE_CURRENT_LIST_DIR}/3rdparty/
)

target_link_libraries(nigf PUBLIC
    GL
    glut
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
)

target_link_libraries(nigf_demo PUBLIC
    nigf
)


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
