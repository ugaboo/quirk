CMAKE_MINIMUM_REQUIRED(VERSION 3.2)
PROJECT(quirk LANGUAGES CXX)

INCLUDE(CMakePrintHelpers)
INCLUDE(ExternalProject)

SET(CMAKE_CXX_STANDARD 20)
SET(CMAKE_CXX_EXTENSIONS OFF)
SET(CMAKE_CXX_STANDARD_REQUIRED ON)

# INCLUDE_DIRECTORIES("${PROJECT_SOURCE_DIR}/src")
# INCLUDE_DIRECTORIES("${PROJECT_SOURCE_DIR}/tests")

SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

# ADD_COMPILE_DEFINITIONS(_ITERATOR_DEBUG_LEVEL=0)

#--------------------------------------------------------------------------------------------------
# external libraries

INCLUDE(FetchContent)

FetchContent_Declare(utf8proc
    GIT_REPOSITORY    https://github.com/JuliaStrings/utf8proc
    GIT_TAG           v2.6.1
    SOURCE_DIR        "${CMAKE_BINARY_DIR}/utf8proc-src"
    BINARY_DIR        "${CMAKE_BINARY_DIR}/utf8proc-build"
)
FetchContent_MakeAvailable(utf8proc)

FetchContent_Declare(magic_enum
    GIT_REPOSITORY    https://github.com/Neargye/magic_enum
    GIT_TAG           v0.7.3
    SOURCE_DIR        "${CMAKE_BINARY_DIR}/magic_enum-src"
    BINARY_DIR        "${CMAKE_BINARY_DIR}/magic_enum-build"
)
FetchContent_MakeAvailable(magic_enum)

FetchContent_Declare(fmt
    GIT_REPOSITORY    https://github.com/fmtlib/fmt
    GIT_TAG           8.0.1
    SOURCE_DIR        "${CMAKE_BINARY_DIR}/fmt-src"
    BINARY_DIR        "${CMAKE_BINARY_DIR}/fmt-build"
)
FetchContent_MakeAvailable(fmt)
INCLUDE_DIRECTORIES("${CMAKE_BINARY_DIR}/fmt-src/include")

#--------------------------------------------------------------------------------------------------
# LLVM

FIND_PACKAGE(LLVM REQUIRED CONFIG)
MESSAGE(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
MESSAGE(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")
INCLUDE_DIRECTORIES(${LLVM_INCLUDE_DIRS})
ADD_DEFINITIONS(${LLVM_DEFINITIONS})
LLVM_MAP_COMPONENTS_TO_LIBNAMES(llvm_libs core support nativecodegen x86asmparser)

#--------------------------------------------------------------------------------------------------
# compiler

FILE(GLOB_RECURSE compiler_h CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/src/*.h")
FILE(GLOB_RECURSE compiler_cpp CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/src/*.cpp")
# cmake_print_variables(compiler_h)
# cmake_print_variables(compiler_cpp)

IF (MSVC)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /WX /external:I \"${LLVM_DIR}/../../../include\" /external:W0")
    MESSAGE("CXXFLAGS: ${CMAKE_CXX_FLAGS}")
ELSE()
    ADD_COMPILE_OPTIONS(-Werror)
    # ADD_COMPILE_OPTIONS(-Wall -Wextra -pedantic -Werror -isystem)
ENDIF()

ADD_LIBRARY(compiler STATIC ${compiler_h} ${compiler_cpp})

TARGET_LINK_LIBRARIES(compiler utf8proc magic_enum fmt ${llvm_libs})

ADD_EXECUTABLE(quirk src/main.cpp)

TARGET_LINK_LIBRARIES(quirk compiler)

#--------------------------------------------------------------------------------------------------
# unit tests

ADD_COMPILE_DEFINITIONS(TEST_DIR="${PROJECT_SOURCE_DIR}/tests/")

ENABLE_TESTING()

ADD_EXECUTABLE(reader_test tests/reader_test.cpp)
ADD_EXECUTABLE(scanner_test tests/scanner_test.cpp)
ADD_EXECUTABLE(parser_test tests/parser_test.cpp)
ADD_EXECUTABLE(scope_builder_test tests/scope_builder_test.cpp)
ADD_EXECUTABLE(codegen_test tests/codegen_test.cpp)

TARGET_LINK_LIBRARIES(reader_test compiler)
TARGET_LINK_LIBRARIES(scanner_test compiler)
TARGET_LINK_LIBRARIES(parser_test compiler)
TARGET_LINK_LIBRARIES(scope_builder_test compiler)
TARGET_LINK_LIBRARIES(codegen_test compiler)

ADD_TEST(NAME reader_test COMMAND $<TARGET_FILE:reader_test>)
ADD_TEST(NAME scanner_test COMMAND $<TARGET_FILE:scanner_test>)
ADD_TEST(NAME parser_test COMMAND $<TARGET_FILE:parser_test>)
ADD_TEST(NAME scope_builder_test COMMAND $<TARGET_FILE:scope_builder_test>)
ADD_TEST(NAME codegen_test COMMAND $<TARGET_FILE:codegen_test>)
