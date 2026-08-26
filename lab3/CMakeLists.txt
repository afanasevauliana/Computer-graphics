cmake_minimum_required(VERSION 3.16)
project(lab3 LANGUAGES CXX)

add_executable(list1 list1.cpp)
add_executable(list2 list2.cpp)
add_executable(list3 list3.cpp)
add_executable(list4 list4.cpp)

foreach(target list1 list2 list3 list4)
    target_compile_features(${target} PRIVATE cxx_std_11)
    target_include_directories(${target} PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}"
    )
endforeach()

if(MINGW)
    target_link_libraries(list1 PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/../lab1/glut32.dll"
        opengl32
    )
    target_link_libraries(list2 PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/../lab1/glut32.dll"
        opengl32
    )
    target_link_libraries(list3 PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/../lab1/glut32.dll"
        opengl32
        glu32
    )
    target_link_libraries(list4 PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/../lab1/glut32.dll"
        opengl32
        glu32
    )
else()
    message(FATAL_ERROR "Для этой лабораторной работы используйте MinGW")
endif()

add_custom_command(TARGET list1 POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${CMAKE_CURRENT_SOURCE_DIR}/../lab1/glut32.dll"
            "$<TARGET_FILE_DIR:list1>/glut32.dll"
)

foreach(target list2 list3 list4)
    add_custom_command(TARGET ${target} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
                "${CMAKE_CURRENT_SOURCE_DIR}/../lab1/glut32.dll"
                "$<TARGET_FILE_DIR:${target}>/glut32.dll"
    )
endforeach()
