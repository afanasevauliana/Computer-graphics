cmake_minimum_required(VERSION 3.16)
project(lab4 LANGUAGES CXX)

if(NOT MINGW)
    message(FATAL_ERROR "Для этой лабораторной работы используйте MinGW")
endif()

set(LAB_TARGETS
    list1
    list2
    list3
    list4
    list5
    list6
    list7
    list8
    list9
)

foreach(target IN LISTS LAB_TARGETS)
    add_executable(${target} "${target}.cpp")
    target_compile_features(${target} PRIVATE cxx_std_11)
    target_include_directories(${target} PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}"
    )
    target_link_libraries(${target} PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/glut32.dll"
        opengl32
        glu32
    )

    add_custom_command(TARGET ${target} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
                "${CMAKE_CURRENT_SOURCE_DIR}/glut32.dll"
                "$<TARGET_FILE_DIR:${target}>/glut32.dll"
    )
endforeach()
