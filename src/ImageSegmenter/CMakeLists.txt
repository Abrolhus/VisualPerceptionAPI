cmake_minimum_required(VERSION 2.8)
project(image_segmenter)
set(SOURCES
        Image_Region.cpp
        Segmented_Image.cpp
        field_border.cpp
        ransac_test.cpp
        ransac_line2d.cpp
        RelativeCoord.cpp
        CartesianCoord.cpp
        Math.cpp
    )
add_library(Image_Segmenter_lib STATIC ${SOURCES})
target_link_libraries(Image_Segmenter_lib img_proc_lib)
target_include_directories(Image_Segmenter_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/..) # /src

