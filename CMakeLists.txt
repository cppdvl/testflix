#julian guarin testflix

cmake_minimum_required(VERSION 3.17)
project(testflix)

set(CMAKE_VERBOSE_MAKEFILE true)
set(CMAKE_CXX_STANDARD 17)

include(FetchContent)
FetchContent_Declare(json
        GIT_REPOSITORY https://github.com/nlohmann/json.git
        GIT_TAG v3.7.3)
FetchContent_GetProperties(json)
if(NOT json_POPULATED)
        FetchContent_Populate(json)
        add_subdirectory(${json_SOURCE_DIR} ${json_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()


add_executable(testflix main.cpp)
target_include_directories(testflix PRIVATE cxxopts-2.2.1/include)
target_link_libraries(testflix PRIVATE nlohmann_json::nlohmann_json)

add_custom_command(
        TARGET testflix POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/data.json $<TARGET_FILE_DIR:${PROJECT_NAME}>
        )