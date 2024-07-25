cmake_minimum_required(VERSION 3.5.0)

project(sct-attacker VERSION 0.1.0 LANGUAGES C CXX)

set(SOURCE_FILES 
    attacker/src/main.c
)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} sct-mem-api)

project(sct-test VERSION 0.1.0 LANGUAGES C CXX)

set(SOURCE_FILES 
    test/src/main.c
)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
