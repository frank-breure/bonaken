project(bonaken)

cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(COMMON_COMPILE_C_OPTIONS
	$<$<OR:$<C_COMPILER_ID:Clang>,$<C_COMPILER_ID:AppleClang>,$<C_COMPILER_ID:GNU>>:-Wall -Wextra -Wpedantic -Werror -fPIC>
	$<$<C_COMPILER_ID:MSVC>:/Wall /WX /wd4113 /wd4255 /wd4668 /wd4710 /wd4711 /wd4820 /wd5045>
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

enable_testing()
add_subdirectory(test)