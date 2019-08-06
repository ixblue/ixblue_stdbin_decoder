cmake_minimum_required(VERSION 2.8.3)
project(iXblue_stdbin_decoder)
set(CMAKE_BUILD_TYPE Debug)
## Compile as C++11, supported in ROS Kinetic and newer
add_compile_options(-std=c++11)

## System dependencies are found with CMake's conventions
find_package(Boost REQUIRED COMPONENTS system)


###########
## Build ##
###########

include_directories(include)

aux_source_directory(src SOURCES)
## Declare a C++ library
add_library(${PROJECT_NAME} SHARED ${SOURCES})

#############
## Install ##
#############

## Mark executables and/or libraries for installation
install(
	TARGETS ${PROJECT_NAME} 
	ARCHIVE DESTINATION lib
  	LIBRARY DESTINATION lib
)

## Mark cpp header files for installation
install(
	DIRECTORY include
	DESTINATION ${CMAKE_INSTALL_PREFIX}
	FILES_MATCHING PATTERN "*.h"
	PATTERN ".git" EXCLUDE
)

#############
## Testing ##
#############

## --- code copied from https://crascit.com/2015/07/25/cmake-gtest/

# Download and unpack googletest at configure time
configure_file(cmake/gtest_download.cmake.in googletest-download/CMakeLists.txt)
execute_process(COMMAND "${CMAKE_COMMAND}" -G "${CMAKE_GENERATOR}" .
    WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/googletest-download" )
execute_process(COMMAND "${CMAKE_COMMAND}" --build .
    WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/googletest-download" )

# Add googletest directly to our build. This adds
# the following targets: gtest, gtest_main, gmock
# and gmock_main
add_subdirectory("${CMAKE_BINARY_DIR}/googletest-src"
                 "${CMAKE_BINARY_DIR}/googletest-build")

# The gtest/gmock targets carry header search path
# dependencies automatically when using CMake 2.8.11 or
# later. Otherwise we have to add them here ourselves.
if(CMAKE_VERSION VERSION_LESS 2.8.11)
    include_directories("${gtest_SOURCE_DIR}/include")
endif()

## ---

enable_testing()

## Add gtest based cpp test target and link libraries
add_executable(memory_blocs_parser_navigation-test test/memory_blocs_parser_navigation.test.cc)
target_link_libraries(memory_blocs_parser_navigation-test ${PROJECT_NAME} ${Boost_LIBRARIES} gtest)
add_test(NAME memory_blocs_parser_navigation_test COMMAND memory_blocs_parser_navigation-test WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/test)																		

add_executable(memory_blocs_parser_extended_navigation-test test/memory_blocs_parser_extended_navigation.test.cc)
target_link_libraries(memory_blocs_parser_extended_navigation-test ${PROJECT_NAME} ${Boost_LIBRARIES} gtest)
add_test(NAME memory_blocs_parser_extended_navigation-test COMMAND memory_blocs_parser_extended_navigation-test WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/test)

add_executable(memory_blocs_parser_external_data-test test/memory_blocs_parser_external_data.test.cc)
target_link_libraries(memory_blocs_parser_external_data-test ${PROJECT_NAME} ${Boost_LIBRARIES} gtest)
add_test(NAME memory_blocs_parser_external_data-test COMMAND memory_blocs_parser_external_data-test WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/test)

add_executable(stdbin_decoder-test test/stdbin_decoder.test.cc)
target_link_libraries(stdbin_decoder-test ${PROJECT_NAME} ${Boost_LIBRARIES} gtest)
add_test(NAME stdbin_decoder-test COMMAND stdbin_decoder-test WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/test)

