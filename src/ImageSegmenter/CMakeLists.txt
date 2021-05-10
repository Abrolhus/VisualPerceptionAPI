cmake_minimum_required(VERSION 2.8)
project(image_segmenter)
set(SOURCES
        Image_Segmenter.cpp
        Image_Region.cpp
    )
set(IMAGE_SEGMENTER_LIB ImageSegmenter_lib PARENT_SCOPE)
add_library(ImageSegmenter_lib STATIC ${SOURCES})
#target_include_directories(ImageSegmenter_lib PUBLIC ..)
#add_dependencies(ImageSegmenter_lib ${IMG_PROC_LIB})
#target_link_directories(ImageSegmenter_lib  PUBLIC ../img_proc)
#message(teste ${IMG_PROC_LIB})
#target_link_libraries(ImageSegmenter_lib ${IMG_PROC_LIB})
#target_include_directories(ImageSegmenter_lib BEFORE PUBLIC ../img_proc)

