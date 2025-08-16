# Minimum CMake version
cmake_minimum_required(VERSION 3.10)

# Project name
project(Seeallyfy)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add source files
file(GLOB SOURCES "src/*.cpp")

# Find OpenCV
find_package(OpenCV REQUIRED)
if(NOT OpenCV_FOUND)
    message(FATAL_ERROR "OpenCV not found. Please install OpenCV and set the OpenCV_DIR variable.")
endif()




# Check if includes/zlib exists and define WITH_COMPRESSION macro
if(EXISTS "${CMAKE_SOURCE_DIR}/includes/zlib")
    add_compile_definitions(WITH_COMPRESSION)
    include_directories(${OpenCV_INCLUDE_DIRS} includes includes/zlib)
else()
    include_directories(${OpenCV_INCLUDE_DIRS} includes)
endif()

# Add executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Link OpenCV libraries
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})

# Automatically copy OpenCV and FFmpeg DLLs to the output folder

#For windows
if(WIN32)
    set(OpenCV_BIN_DIR ${OpenCV_DIR}/bin)

    # Find all OpenCV and FFmpeg DLLs
    file(GLOB OPENCV_DLLS
        "${OpenCV_BIN_DIR}/opencv_videoio_ffmpeg*.dll"
    )

    # Output directory (where the executable is built)
    set(OUTPUT_DIR "$<TARGET_FILE_DIR:${PROJECT_NAME}>")

    # Copy each DLL after build
    foreach(DLL ${OPENCV_DLLS})
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${DLL}" "${OUTPUT_DIR}"
        )
    endforeach()
endif()
