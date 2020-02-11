# CMakeList.txt : CMake project for Test_Cross_Compile, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
add_executable (Test_Cross_Compile "Test_Cross_Compile.cpp" "Test_Cross_Compile.h")

# TODO: Add tests and install targets if needed.
find_package(Boost 1.67.0 REQUIRED COMPONENTS system filesystem REQUIRED)
find_package(fmt)

INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR} )
TARGET_LINK_LIBRARIES(Test_Cross_Compile LINK_PUBLIC ${Boost_LIBRARIES} fmt::fmt )

