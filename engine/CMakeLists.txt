cmake_minimum_required(VERSION 3.2)
cmake_policy(SET CMP0091 NEW)
cmake_policy(SET CMP0042 NEW)

project(shallow_blue)

add_definitions(-DNAPI_VERSION=4)

include_directories(${CMAKE_JS_INC})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(OUTPUT "debug" CACHE STRING "binary output, default: debug")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin/${OUTPUT}")

# -- Do not remove tags below if you desire cmkr dependency building -- #
#CMAKER_SET
#CMAKER_FIND
# -- End CMaker -- #

add_subdirectory(src)
