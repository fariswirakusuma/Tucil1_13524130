set(CMAKE_C_COMPILER /usr/bin/gcc)
set(CMAKE_CXX_COMPILER /usr/bin/g++)
cmake_minimum_required(VERSION 3.10)
project(QueenSolver)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

find_package(wxWidgets REQUIRED COMPONENTS core base)
include(${wxWidgets_USE_FILE})

find_package(OpenCV REQUIRED)

include_directories(
    src/include
    ${OpenCV_INCLUDE_DIRS}
    ${wxWidgets_INCLUDE_DIRS}
)

set(SOURCES
    src/allqueendirec.cpp
    src/inputfile.cpp
    src/outputarr.cpp
    src/wx_ui.cpp
)

add_executable(app ${SOURCES})

# Kadang perlu link tambahan untuk multithreading yang diminta wxWidgets
target_link_libraries(app 
    ${wxWidgets_LIBRARIES} 
    ${OpenCV_LIBS}
)

add_custom_command(TARGET app POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E create_symlink 
    ${CMAKE_CURRENT_SOURCE_DIR}/test 
    ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/test
)