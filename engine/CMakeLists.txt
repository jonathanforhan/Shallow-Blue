cmake_minimum_required(VERSION 3.2)
cmake_policy(SET CMP0091 NEW)
cmake_policy(SET CMP0042 NEW)

project(shallow_blue)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

# NAPI includes
add_definitions(-DNAPI_VERSION=3)
include_directories(${CMAKE_JS_INC})
execute_process(COMMAND node -p "require('node-addon-api').include"
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        OUTPUT_VARIABLE NODE_ADDON_API_DIR
        )
string(REPLACE "\n" "" NODE_ADDON_API_DIR ${NODE_ADDON_API_DIR})
string(REPLACE "\"" "" NODE_ADDON_API_DIR ${NODE_ADDON_API_DIR})

add_subdirectory(src)
