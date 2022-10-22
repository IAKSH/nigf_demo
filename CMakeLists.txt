cmake_minimum_required(VERSION 3.0.0)
project(nigf_demo VERSION 0.1.0)

include(CTest)
enable_testing()

add_library(nigf)

target_sources(nigf PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/source/gameplay.cpp
    ${CMAKE_CURRENT_LIST_DIR}/source/gameplay.hpp
    ${CMAKE_CURRENT_LIST_DIR}/source/image.cpp
    ${CMAKE_CURRENT_LIST_DIR}/source/image.hpp
    ${CMAKE_CURRENT_LIST_DIR}/source/msgobject.cpp
    ${CMAKE_CURRENT_LIST_DIR}/source/msgobject.hpp
    ${CMAKE_CURRENT_LIST_DIR}/source/gamespirite.cpp
    ${CMAKE_CURRENT_LIST_DIR}/source/gamespirite.hpp
    ${CMAKE_CURRENT_LIST_DIR}/source/gameplay.cpp
    ${CMAKE_CURRENT_LIST_DIR}/source/gameplay.hpp
    ${CMAKE_CURRENT_LIST_DIR}/source/gameobject.cpp
    ${CMAKE_CURRENT_LIST_DIR}/source/gameobject.hpp
    ${CMAKE_CURRENT_LIST_DIR}/source/animation.cpp
    ${CMAKE_CURRENT_LIST_DIR}/source/animation.hpp
)

target_include_directories(nigf PUBLIC 
    ${CMAKE_CURRENT_LIST_DIR}/3rdparty/
)

target_link_libraries(nigf PUBLIC
    GL
    glut
)

add_executable(nigf_demo test_main.cpp)

target_include_directories(nigf_demo PUBLIC 
    ${CMAKE_CURRENT_LIST_DIR}/source/
)

target_link_libraries(nigf_demo PUBLIC
    nigf
)


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
