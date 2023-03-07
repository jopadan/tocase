cmake_minimum_required(VERSION 3.25.0 FATAL_ERROR)
project(tocase LANGUAGES CXX)

set(PROJECT_VERSION 1.0)
set(PROJECT_DESCRIPTION "tocase - single-file header-only recursive unicode
path case convert using icu written in C++")

include(GNUInstallDirs)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_compile_options(-march=native -O3)
add_compile_options(-D_FILE_OFFSET_BITS=64)
add_compile_options(-fdata-sections)
add_compile_options(-ffunction-sections)
add_compile_options(-Wall)
add_compile_options(-Wextra)
add_compile_options(-Wpedantic)
add_link_options(-Wl,--gc-sections)
#add_link_options(-Wl,--print-gc-sections)
add_link_options(-Wl,-s)

# external dependencies
find_package(ICU)

# pup executable
include_directories(${ICU_INCLUDE_DIRS} $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>)
link_libraries(icuuc)

add_executable(tocase tocase.cpp) 
set_target_properties(tocase PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

install(TARGETS tocase EXPORT ${PROJECT_NAME}Export
	ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
	RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
	)

