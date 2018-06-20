cmake_minimum_required(VERSION 3.5)
project(Sorting_Competition)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Ofast -march=native -frename-registers")

set(SOURCE_FILES stl.cpp)
add_executable(Sorting_Competition_stl ${SOURCE_FILES})

set(SOURCE_FILES stl2.cpp)
add_executable(Sorting_Competition_stl2 ${SOURCE_FILES})

set(SOURCE_FILES lowstl.cpp)
add_executable(Sorting_Competition_lowstl ${SOURCE_FILES})

set(SOURCE_FILES lowstl2.cpp)
add_executable(Sorting_Competition_lowstl2 ${SOURCE_FILES})

set(SOURCE_FILES custom.cpp)
add_executable(Sorting_Competition_custom ${SOURCE_FILES})

set(SOURCE_FILES customSIMD.cpp)
add_executable(Sorting_Competition_customSIMD ${SOURCE_FILES})
add_executable(Sorting_Competition_customSIMDo ${SOURCE_FILES})

if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    target_link_libraries(Sorting_Competition_customSIMD ${CMAKE_SOURCE_DIR}/libamac64.a)
    target_link_libraries(Sorting_Competition_customSIMDo ${CMAKE_SOURCE_DIR}/libamac64o.a)
else ()
    target_link_libraries(Sorting_Competition_customSIMD ${CMAKE_SOURCE_DIR}/libaelf64.a)
    target_link_libraries(Sorting_Competition_customSIMDo ${CMAKE_SOURCE_DIR}/libaelf64o.a)
endif ()
