# CMakeList.txt : CMake project for Test_Cross_Compile, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
add_executable (Test_Cross_Compile "Test_Cross_Compile.cpp" "Test_Cross_Compile.h" "SocketHelper.h")

# TODO: Add tests and install targets if needed.
find_package(Boost 1.67.0 REQUIRED COMPONENTS system filesystem thread REQUIRED)
find_package(fmt CONFIG REQUIRED)

find_path(FLATBUFFERS_INCLUDE_DIR NAMES flatbuffers/flatbuffers.h)

include_directories( ${Boost_INCLUDE_DIR} )
include_directories( ${FLATBUFFERS_INCLUDE_DIR} )

TARGET_LINK_LIBRARIES(Test_Cross_Compile PRIVATE ${Boost_LIBRARIES} fmt::fmt)

set_property(TARGET Test_Cross_Compile PROPERTY CXX_STANDARD 17)
set_property(TARGET Test_Cross_Compile PROPERTY CXX_STANDARD_REQUIRED ON)