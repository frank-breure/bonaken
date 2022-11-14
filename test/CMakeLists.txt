project(test_bonaken LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        release-1.12.0
)
FetchContent_MakeAvailable(googletest)
add_library(GTest::GTest INTERFACE IMPORTED)
target_link_libraries(GTest::GTest INTERFACE gtest_main)

list(APPEND test_sources
	test_bonaken.cc
	test_random.cc
	)

include(GoogleTest)

add_executable(${PROJECT_NAME} ${test_sources})

gtest_add_tests(
	TARGET      ${PROJECT_NAME}
    TEST_SUFFIX .noArgs
    TEST_LIST   noArgsTests
	)

gtest_discover_tests(${PROJECT_NAME} 
	XML_OUTPUT_DIR "${CMAKE_BINARY_DIR}"
	)

target_compile_options(${PROJECT_NAME}
	PRIVATE
		${COMMON_COMPILE_CXX_OPTIONS}
	)

target_include_directories(${PROJECT_NAME}
	PRIVATE
		..)

target_link_libraries(${PROJECT_NAME}
	PRIVATE
  		GTest::GTest
  		bonaken)

add_test(bonaken_gtests ${PROJECT_NAME})
