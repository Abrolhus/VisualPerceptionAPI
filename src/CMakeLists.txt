include_directories(${CMAKE_CURRENT_SOURCE_DIR})
add_subdirectory(img_proc)
add_subdirectory(file_proc)

set(SOURCES
    dummy.cpp
    )
add_executable(run main.cpp ${SOURCES})
target_link_libraries(run PUBLIC ${OpenCV_LIBS})
target_link_libraries(run PRIVATE ${IMG_PROC_LIB})
target_link_libraries(run PRIVATE ${FILE_PROC_LIB})
