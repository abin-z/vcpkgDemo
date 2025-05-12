add_executable(main main.cpp)
target_include_directories(main INTERFACE ${CMAKE_CURRENT_LIST_DIR})

target_link_libraries(main PRIVATE fmt::fmt)        # fmt库
target_link_libraries(main PRIVATE CLI11::CLI11)    # CLI11库