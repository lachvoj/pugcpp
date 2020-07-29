cmake_minimum_required (VERSION 3.1.00)

project (pugcpp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
set(LIB_SRC_DIR ${SRC_DIR}/lib)
set(TEST_SRC_DIR ${SRC_DIR}/test)
set(PROJECT_INCLUDE_DIR )
set(ADDITIONAL_COMPILE_FLAGS "-Wall -g")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${ADDITIONAL_COMPILE_FLAGS}")

# message(src dir: ${SRC_DIR})
# message(lib src dir: ${LIB_SRC_DIR})
# message(test src dir: ${TEST_SRC_DIR})

# custom targets
add_custom_target(debug
    COMMAND ${CMAKE_COMMAND} -DCMAKE_BUILD_TYPE=Debug ${CMAKE_SOURCE_DIR}
    COMMAND ${CMAKE_COMMAND} --build ${CMAKE_SOURCE_DIR} --target all -- -j4
    COMMENT "Switch CMAKE_BUILD_TYPE to Debug"
)

add_custom_target(release
    COMMAND ${CMAKE_COMMAND} -DCMAKE_BUILD_TYPE=Release ${CMAKE_SOURCE_DIR}
    COMMAND ${CMAKE_COMMAND} --build ${CMAKE_SOURCE_DIR} --target all -- -j4
    COMMENT "Switch CMAKE_BUILD_TYPE to Release"
)

add_custom_target(doc
    COMMAND doxygen Doxyfile
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
)

add_custom_target(formatSources
    COMMAND find src/ -iname *.hpp -o -iname *.cpp | xargs clang-format -i -style=file
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
)

#if missing headers install g++-8 !!!
add_custom_target(runStaticAnalysis
    COMMAND ${CMAKE_COMMAND} -DCMAKE_CXX_COMPILER=clang++ -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_FLAGS_SA:STRING="-stdlib=libstdc++" -DCMAKE_BUILD_TYPE=SA ${CMAKE_SOURCE_DIR}
    COMMAND scan-build -o ./saResults make -j4
    COMMAND ${CMAKE_COMMAND} -DCMAKE_CXX_COMPILER=g++ -DCMAKE_C_COMPILER=gcc ${CMAKE_SOURCE_DIR}
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
)

#add lib source files
file(GLOB_RECURSE SRC_LIB_FILES ${LIB_SRC_DIR}/*.cpp)
message(lib files: ${SRC_LIB_FILES})

#add test source files
file(GLOB_RECURSE SRC_TEST_FILES ${TEST_SRC_DIR}/*.cpp)
message(test files: ${SRC_TEST_FILES})

#generate static lib
add_library(${PROJECT_NAME} ${SRC_LIB_FILES})

#generate test executable
set(TEST_BIN_NAME ${PROJECT_NAME}Test)
add_executable(${TEST_BIN_NAME} ${SRC_TEST_FILES})
target_link_libraries(${TEST_BIN_NAME} ${PROJECT_NAME} stdc++fs)