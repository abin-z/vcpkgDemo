add_executable(main main.cpp)
target_include_directories(main INTERFACE ${CMAKE_CURRENT_LIST_DIR})

target_link_libraries(main PRIVATE fmt::fmt)        # fmt库
target_link_libraries(main PRIVATE CLI11::CLI11)    # CLI11库
target_link_libraries(main PRIVATE nlohmann_json::nlohmann_json)    # nlohmann_json库
target_link_libraries(main PRIVATE range-v3::range-v3)  # range-v3库