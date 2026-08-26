cmake_minimum_required(VERSION 3.16)
project(lab5 LANGUAGES CXX)

if(NOT MINGW)
    message(FATAL_ERROR "Для этой лабораторной работы используйте MinGW")
endif()

set(LAB_CANDIDATES
    list1
    list2
    list3
    list4
)

set(LAB_TARGETS)
foreach(target IN LISTS LAB_CANDIDATES)
    if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/${target}.cpp")
        list(APPEND LAB_TARGETS ${target})
    endif()
endforeach()

set(GLUT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../lab4")

foreach(target IN LISTS LAB_TARGETS)
    add_executable(${target} "${target}.cpp")
    target_compile_features(${target} PRIVATE cxx_std_11)
    target_include_directories(${target} PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}"
        "${GLUT_DIR}"
    )
    target_link_libraries(${target} PRIVATE
        "${GLUT_DIR}/glut32.dll"
        opengl32
        glu32
    )

    add_custom_command(TARGET ${target} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
                "${GLUT_DIR}/glut32.dll"
                "$<TARGET_FILE_DIR:${target}>/glut32.dll"
    )
endforeach()

add_custom_command(TARGET list1 POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${CMAKE_CURRENT_SOURCE_DIR}/stone.tga"
            "$<TARGET_FILE_DIR:list1>/stone.tga"
)

set(LIST3_TEXTURES
    brick.tga
    wood.tga
    stone.tga
    tiles.tga
    metal.tga
)

foreach(texture IN LISTS LIST3_TEXTURES)
    add_custom_command(TARGET list3 POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
                "${CMAKE_CURRENT_SOURCE_DIR}/${texture}"
                "$<TARGET_FILE_DIR:list3>/${texture}"
    )
endforeach()
