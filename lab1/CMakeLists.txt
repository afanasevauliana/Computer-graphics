cmake_minimum_required(VERSION 3.16)
project(lab1 LANGUAGES CXX)

add_executable(list2 list2.cpp)
add_executable(list3_4 list3_4.cpp)
add_executable(list5 list5.cpp)

set(LAB_TARGETS list2 list3_4 list5)
foreach(target IN LISTS LAB_TARGETS)
    target_compile_features(${target} PRIVATE cxx_std_11)
    target_include_directories(${target} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")
endforeach()

if(MINGW)
    foreach(target IN LISTS LAB_TARGETS)
        target_link_libraries(${target} PRIVATE
            "${CMAKE_CURRENT_SOURCE_DIR}/glut32.dll"
            opengl32
        )
    endforeach()
elseif(MSVC)
    message(FATAL_ERROR "Эта конфигурация рассчитана на MinGW из VS Code, а не MSVC.")
else()
    message(FATAL_ERROR "Для этой Windows-лабораторной используйте MinGW.")
endif()

add_custom_command(TARGET list2 POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${CMAKE_CURRENT_SOURCE_DIR}/glut32.dll"
            "$<TARGET_FILE_DIR:list2>/glut32.dll"
)
