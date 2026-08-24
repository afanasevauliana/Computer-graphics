cmake_minimum_required(VERSION 3.16)
project(lab2 LANGUAGES CXX)

add_executable(list1 list1.cpp)
add_executable(list2 list2.cpp)
add_executable(list3 list3.cpp)
add_executable(list4 list4.cpp)
add_executable(list5 list5.cpp)
add_executable(list6 list6.cpp)
add_executable(list7 list7.cpp)
add_executable(list8 list8.cpp)
add_executable(list9 list9.cpp)

set(LAB_TARGETS list1 list2 list3 list4 list5 list6 list7 list8 list9)
foreach(target IN LISTS LAB_TARGETS)
    target_compile_features(${target} PRIVATE cxx_std_11)
    target_include_directories(${target} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")
endforeach()

if(MINGW)
    foreach(target IN LISTS LAB_TARGETS)
        target_link_libraries(${target} PRIVATE
            "${CMAKE_CURRENT_SOURCE_DIR}/../lab1/glut32.dll"
            opengl32
        )
    endforeach()
else()
    message(FATAL_ERROR "Для этой лабораторной работы используйте MinGW.")
endif()

add_custom_command(TARGET list1 POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${CMAKE_CURRENT_SOURCE_DIR}/../lab1/glut32.dll"
            "$<TARGET_FILE_DIR:list1>/glut32.dll"
)

add_custom_command(TARGET list2 POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${CMAKE_CURRENT_SOURCE_DIR}/../lab1/glut32.dll"
            "$<TARGET_FILE_DIR:list2>/glut32.dll"
)

add_custom_command(TARGET list3 POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${CMAKE_CURRENT_SOURCE_DIR}/../lab1/glut32.dll"
            "$<TARGET_FILE_DIR:list3>/glut32.dll"
)

add_custom_command(TARGET list4 POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${CMAKE_CURRENT_SOURCE_DIR}/../lab1/glut32.dll"
            "$<TARGET_FILE_DIR:list4>/glut32.dll"
)

add_custom_command(TARGET list5 POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${CMAKE_CURRENT_SOURCE_DIR}/../lab1/glut32.dll"
            "$<TARGET_FILE_DIR:list5>/glut32.dll"
)

add_custom_command(TARGET list6 POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${CMAKE_CURRENT_SOURCE_DIR}/../lab1/glut32.dll"
            "$<TARGET_FILE_DIR:list6>/glut32.dll"
)

add_custom_command(TARGET list7 POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${CMAKE_CURRENT_SOURCE_DIR}/../lab1/glut32.dll"
            "$<TARGET_FILE_DIR:list7>/glut32.dll"
)

add_custom_command(TARGET list8 POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${CMAKE_CURRENT_SOURCE_DIR}/../lab1/glut32.dll"
            "$<TARGET_FILE_DIR:list8>/glut32.dll"
)

add_custom_command(TARGET list9 POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${CMAKE_CURRENT_SOURCE_DIR}/../lab1/glut32.dll"
            "$<TARGET_FILE_DIR:list9>/glut32.dll"
)
