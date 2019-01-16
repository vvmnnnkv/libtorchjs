cmake_minimum_required(VERSION 3.1 FATAL_ERROR)

project(libtorchjs)

# Node-cmake
include(NodeJS.cmake)
nodejs_init()

file(GLOB SRC_FILES "${PROJECT_SOURCE_DIR}/src/*.cc" "${PROJECT_SOURCE_DIR}/src/*.h")
add_nodejs_module(${PROJECT_NAME} ${SRC_FILES})

# Look for shared libs in the same folder
IF (UNIX)
    set(CMAKE_MODULE_LINKER_FLAGS "${CMAKE_MODULE_LINKER_FLAGS} -Wl,-rpath,$ORIGIN")
    set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -Wl,-rpath,$ORIGIN")
ENDIF(UNIX)

set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 11)

# Include N-API wrappers
target_include_directories(${PROJECT_NAME} PRIVATE "${CMAKE_SOURCE_DIR}/node_modules/node-addon-api")

find_package(Torch PATHS "./libtorch/" REQUIRED)
target_link_libraries(${PROJECT_NAME} "${TORCH_LIBRARIES}")
