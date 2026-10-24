cmake_minimum_required(VERSION 3.16)

set(CMAKE_PROJECT_INCLUDE_BEFORE "${CMAKE_CURRENT_SOURCE_DIR}/cmake/EnableCMP0048.cmake")

project(bonaken LANGUAGES CXX VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(COMMON_COMPILE_CXX_OPTIONS
	$<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:GNU>>:-Wall -Wextra -Wpedantic -Werror -fPIC>
	$<$<CXX_COMPILER_ID:MSVC>:/Wall /WX /wd4113 /wd4255 /wd4668 /wd4710 /wd4711 /wd4820 /wd5045>
	)

list(APPEND sources
	bonaken.cc
	bonaken.h
	random.cc)

add_library(${PROJECT_NAME} ${sources})

target_compile_options(${PROJECT_NAME}
	PRIVATE
		${COMMON_COMPILE_C_OPTIONS}
	)

set(PROGRAM "bonaak")
list(APPEND main_sources
	bonaak.cc
	)

add_executable(${PROGRAM} ${main_sources})

target_compile_options(${PROGRAM}
	PRIVATE
		${COMMON_COMPILE_CXX_OPTIONS}
	)

target_include_directories(${PROGRAM}
	PRIVATE
		..)

target_link_libraries(${PROGRAM}
	PRIVATE
		bonaken)

enable_testing()
add_subdirectory(test)
