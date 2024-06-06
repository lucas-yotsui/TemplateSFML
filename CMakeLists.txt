cmake_minimum_required(VERSION 3.28)
cmake_policy(SET CMP0127 NEW)
cmake_policy(SET CMP0135 NEW)
include(FetchContent)

# Export compile commands for clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

# Project definition
project(knn
	VERSION 0.0.1
	DESCRIPTION "Implementations of KNN algorithm"
	LANGUAGES CXX
)
file(GLOB_RECURSE SOURCES ${CMAKE_SOURCE_DIR}/source/*.cpp ${CMAKE_SOURCE_DIR}/include/*.h)
add_executable(${CMAKE_PROJECT_NAME} ${SOURCES})
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic -Wno-strict-aliasing)

# Fetch dependencies
set(BUILD_SHARED_LIBS OFF)
set(FETCHCONTENT_QUIET FALSE)

message(STATUS "+--------------------------------------------------------------+")
message(STATUS "|           Fetching fmt and adding it to the project          |")
message(STATUS "+--------------------------------------------------------------+")
FetchContent_Declare(fmt URL https://github.com/fmtlib/fmt/releases/download/10.2.0/fmt-10.2.0.zip)
FetchContent_MakeAvailable(fmt)
list(APPEND EXTERNAL_LIBRARIES fmt::fmt)

message(STATUS "+--------------------------------------------------------------+")
message(STATUS "|           Fetching SFML and adding it to the project         |")
message(STATUS "+--------------------------------------------------------------+")
FetchContent_Declare(SFML GIT_REPOSITORY https://github.com/SFML/SFML.git GIT_TAG 2.6.1 GIT_PROGRESS TRUE)
FetchContent_MakeAvailable(SFML)
list(APPEND EXTERNAL_LIBRARIES sfml-graphics)

# Link libraries
target_link_libraries(${CMAKE_PROJECT_NAME} ${EXTERNAL_LIBRARIES})
