include_directories(${CMAKE_CURRENT_SOURCE_DIR})
add_subdirectory(img_proc)
add_subdirectory(file_proc)
add_subdirectory(ImageSegmenter)

set(SOURCES
    dummy.cpp
    )
add_executable(run main.cpp ${SOURCES})
target_link_libraries(run
        ${OpenCV_LIBS}
        ${IMG_PROC_LIB}
        ${FILE_PROC_LIB}
        ${IMAGE_SEGMENTER_LIB})
