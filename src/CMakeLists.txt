include_directories(${CMAKE_CURRENT_SOURCE_DIR})
add_subdirectory(img_proc)

set(SOURCES
    dummy.cpp
    )
set(LIB_NAME src_lib)
add_library(${LIB_NAME} STATIC ${SOURCES})
message(${LIB_NAME})


add_executable(run main.cpp)
target_link_libraries(run PRIVATE ${LIB_NAME})
message(teste ${OpenCV_LIBS})
target_link_libraries(run PUBLIC ${OpenCV_LIBS})
message(${IMG_PROC_LIB})
target_link_libraries(run PRIVATE ${IMG_PROC_LIB})
