include_directories(${CMAKE_CURRENT_SOURCE_DIR})
add_subdirectory(img_proc)
add_subdirectory(file_proc)
add_subdirectory(ImageSegmenter)
add_subdirectory(field_color_detection)

set(SOURCES
    dummy.cpp
    )
add_executable(run main.cpp ${SOURCES})
target_link_libraries(run
        ${OpenCV_LIBS}
        img_proc_lib
        file_proc_lib
        Image_Segmenter_lib
        field_color_detection_lib)