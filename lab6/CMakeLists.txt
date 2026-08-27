cmake_minimum_required(VERSION 3.16)
project(lab6 LANGUAGES CXX)

if(NOT MINGW)
    message(FATAL_ERROR "Для этой лабораторной работы используйте MinGW")
endif()

set(GLUT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../lab4")

add_executable(list1 list1.cpp)
target_compile_features(list1 PRIVATE cxx_std_11)
target_include_directories(list1 PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}"
    "${GLUT_DIR}"
)
target_link_libraries(list1 PRIVATE
    "${GLUT_DIR}/glut32.dll"
    opengl32
    glu32
)

add_custom_command(TARGET list1 POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${GLUT_DIR}/glut32.dll"
            "$<TARGET_FILE_DIR:list1>/glut32.dll"
)

add_executable(list2 list2.cpp list3.cpp)
target_compile_features(list2 PRIVATE cxx_std_11)
target_include_directories(list2 PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}"
    "${GLUT_DIR}"
)
target_link_libraries(list2 PRIVATE
    "${GLUT_DIR}/glut32.dll"
    opengl32
    glu32
)

add_custom_command(TARGET list2 POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${GLUT_DIR}/glut32.dll"
            "$<TARGET_FILE_DIR:list2>/glut32.dll"
)

if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/image.tga")
    add_custom_command(TARGET list2 POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
                "${CMAKE_CURRENT_SOURCE_DIR}/image.tga"
                "$<TARGET_FILE_DIR:list2>/image.tga"
    )
endif()

add_executable(list5 list5.cpp list3.cpp)
target_compile_features(list5 PRIVATE cxx_std_11)
target_include_directories(list5 PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}"
    "${GLUT_DIR}"
)
target_link_libraries(list5 PRIVATE
    "${GLUT_DIR}/glut32.dll"
    opengl32
    glu32
)

add_custom_command(TARGET list5 POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${GLUT_DIR}/glut32.dll"
            "$<TARGET_FILE_DIR:list5>/glut32.dll"
)

if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/image.tga")
    add_custom_command(TARGET list5 POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
                "${CMAKE_CURRENT_SOURCE_DIR}/image.tga"
                "$<TARGET_FILE_DIR:list5>/image.tga"
    )
endif()
