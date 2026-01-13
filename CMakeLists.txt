cmake_minimum_required(VERSION 3.10)
project(PrismArcher)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include directories
include_directories(${PROJECT_SOURCE_DIR}/Include)

# Source files
file(GLOB_RECURSE SOURCES "Source/*.cpp")
file(GLOB_RECURSE HEADERS "Include/*.h")

add_executable(PrismArcher WIN32 ${SOURCES} ${HEADERS})

# Link libraries
target_link_libraries(PrismArcher d3d11 d3dcompiler dxgi)

# Set working directory for debugging
set_target_properties(PrismArcher PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}")
