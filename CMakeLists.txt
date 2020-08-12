project(XLog)

set(TARGET XLog)
cmake_minimum_required(VERSION 3.0)
set(CMAKE_CXX_STANDARD 17)

include_directories(
    ${PROJECT_ROOT_DIR}thirdparty/fmt/include/
    ${PROJECT_ROOT_DIR}include/
)
link_directories(${PROJECT_ROOT_DIR}thirdparth/fmt/lib)

file(GLOB HEADERS ${PROJECT_ROOT_DIR}include/*.h)
file(GLOB SOURCES ${PROJECT_ROOT_DIR}source/*.cpp)

add_library(${TARGET} SHARED ${HEADERS} ${SOURCES})
target_link_libraries(${TARGET} fmt)