cmake_minimum_required (VERSION 3.1.00)

project (pugcpp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
set(3D_PT_DIR ${CMAKE_SOURCE_DIR}/3d)
set(LIB_SRC_DIR ${SRC_DIR}/lib)
set(TEST_SRC_DIR ${SRC_DIR}/test)
set(PROJECT_INCLUDE_DIR )
set(ADDITIONAL_COMPILE_FLAGS "-Wall -g")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${ADDITIONAL_COMPILE_FLAGS}")
set(THREADS_PREFER_PTHREAD_FLAG ON)

find_package(Threads REQUIRED)

#download 3d party libs
# #google cel-cpp
# set(CEL_CPP_DIR ${3D_PT_DIR}/cel-cpp/)
# find_path(CEL_CPP ${CEL_CPP_DIR}/celbulklib.a)
# if((NOT CEL_CPP) OR (NOT EXISTS ${CEL_CPP}))
#     message("Unable to find google cell-cpp lib on path: ${CEL_CPP_DIR}")
#     execute_process(COMMAND git submodule update --init -- ${CEL_CPP_DIR})
#     find_program(BAZEL bazel)
#     if(NOT BAZEL)
#         message(FATAL_ERROR "No bazel found!")
#     endif()
#     # execute_process(
#     #     COMMAND bazel build //v1beta1:
#     #     WORKING_DIRECTORY ${CEL_CPP_DIR}
#     find_program(LIBTOOL libtool)
#     if(NOT LIBTOOL)
#         message(FATAL_ERROR "No libtool found!")
#     endif()
#     FILE(GLOB_RECURSE CEL_LIBS FOLLOW_SYMLINKS ${CEL_CPP_DIR}/bazel-bin/*.a )
#     message("${CEL_LIBS}")
#     # execute_process(COMMAND libtool -static -o ${CEL_CPP} ${CEL_LIBS})
# else()
# endif()

#v8
set(V8_DIR ${3D_PT_DIR}/v8)
find_library(V8 libv8_monolith.a PATHS ${V8_DIR}/out.gn/x64.release.sample/obj)
# message("${V8}")
if(NOT V8)
    #depot tools
    set(DT_DIR ${3D_PT_DIR}/depot_tools)
    if(NOT EXISTS ${DT_DIR})
        execute_process(COMMAND git clone --depth 1 https://chromium.googlesource.com/chromium/tools/depot_tools.git ${DT_DIR})
    endif()
    set(ENV{PATH} $ENV{PATH}:${DT_DIR})
    #V8
    if(NOT EXISTS ${V8_DIR})
        execute_process(COMMAND fetch --no-history v8 WORKING_DIRECTORY ${3D_PT_DIR})
    endif()
    execute_process(COMMAND tools/dev/v8gen.py x64.release.sample  WORKING_DIRECTORY ${V8_DIR})
    execute_process(COMMAND ninja -C out.gn/x64.release.sample v8_monolith  WORKING_DIRECTORY ${V8_DIR})
endif()

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
target_link_libraries(${PROJECT_NAME} PRIVATE ${V8} stdc++fs Threads::Threads)
target_include_directories(${PROJECT_NAME} PRIVATE ${V8_DIR}/include)

#generate test executable
set(TEST_BIN_NAME ${PROJECT_NAME}Test)
add_executable(${TEST_BIN_NAME} ${SRC_TEST_FILES})
target_link_libraries(${TEST_BIN_NAME} ${PROJECT_NAME})