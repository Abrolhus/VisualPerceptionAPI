include_directories(${CMAKE_CURRENT_SOURCE_DIR})
add_subdirectory(img_proc)

set(SOURCES
    dummy.cpp
    )
add_executable(run main.cpp ${SOURCES})
target_link_libraries(run PUBLIC ${OpenCV_LIBS})
target_link_libraries(run PRIVATE ${IMG_PROC_LIB})
