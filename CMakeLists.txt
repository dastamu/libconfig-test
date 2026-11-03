cmake_minimum_required(VERSION 3.15)
project(libconfig_test C CXX)

# C++ standard required
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Configuring the libconfig submodule
# The original libconfig repository mainly uses Autotools,
# but the simplest and most reliable way to include it as a submodule
# in CMake is to directly build its source files as a static library.

set(LIBCONFIG_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libconfig/lib)

# Complete list of C source files (added util, wincompat, etc.)
set(LIBCONFIG_C_SOURCES
    ${LIBCONFIG_DIR}/libconfig.c
    ${LIBCONFIG_DIR}/grammar.c
    ${LIBCONFIG_DIR}/scanner.c
    ${LIBCONFIG_DIR}/scanctx.c
    ${LIBCONFIG_DIR}/strbuf.c
    ${LIBCONFIG_DIR}/util.c
    ${LIBCONFIG_DIR}/wincompat.c
    ${LIBCONFIG_DIR}/strvec.c
)

# C++ source file
set(LIBCONFIG_CPP_SOURCES
    ${LIBCONFIG_DIR}/libconfigcpp.c++
)

# We create a local static library target by combining both file types
add_library(libconfig STATIC ${LIBCONFIG_C_SOURCES} ${LIBCONFIG_CPP_SOURCES})

# To be sure, we force CMake to use the appropriate compilers for the files
set_source_files_properties(${LIBCONFIG_C_SOURCES} PROPERTIES LANGUAGE C)
set_source_files_properties(${LIBCONFIG_CPP_SOURCES} PROPERTIES LANGUAGE CXX)

# We indicate the directories with the submodule header files
target_include_directories(libconfig PUBLIC ${LIBCONFIG_DIR})

# Disabling warnings for external library code
if(MSVC)
    target_compile_options(libconfig PRIVATE /W0)
else()
    target_compile_options(libconfig PRIVATE -w)
endif()

# Configuring your program
add_executable(main main.cpp)

# Library linking
target_link_libraries(main PRIVATE libconfig)

# Copying the configuration file to the startup folder
configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/config.cfg
    ${CMAKE_CURRENT_BINARY_DIR}/config.cfg
    COPYONLY
)
