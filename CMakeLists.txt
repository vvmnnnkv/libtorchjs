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

if(WIN32)
  include(CheckCXXCompilerFlag)
  check_cxx_compiler_flag(/d2FH4- HAS_D2FH4)
  if (HAS_D2FH4)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /d2FH4-")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /d2FH4-")
  endif()
ENDIF(WIN32)

# Include N-API wrappers
target_include_directories(${PROJECT_NAME} PRIVATE "${CMAKE_SOURCE_DIR}/node_modules/node-addon-api")

find_package(Torch PATHS "./libtorch/" REQUIRED)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${TORCH_CXX_FLAGS}")
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 14)
target_link_libraries(${PROJECT_NAME} "${TORCH_LIBRARIES}")
