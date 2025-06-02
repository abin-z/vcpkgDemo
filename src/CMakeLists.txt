add_executable(main main.cpp)
target_include_directories(main INTERFACE ${CMAKE_CURRENT_LIST_DIR})

target_link_libraries(main PRIVATE fmt::fmt)        # fmt库
target_link_libraries(main PRIVATE CLI11::CLI11)    # CLI11库
target_link_libraries(main PRIVATE nlohmann_json::nlohmann_json)    # nlohmann_json库
target_link_libraries(main PRIVATE range-v3::range-v3)  # range-v3库
target_link_libraries(main PRIVATE spdlog::spdlog)      # spdlog库


add_executable(iconv_demo iconv_demo.cpp)
target_link_libraries(iconv_demo PRIVATE iconv)  # libiconv库


# 这个变量是 vcpkg 自动设置的，指向安装目录
message(STATUS "VCPKG_INSTALLED_DIR = ${VCPKG_INSTALLED_DIR}")
add_executable(base64 base64.cpp)
# 纯头文件库统一从include目录包含
target_include_directories(base64
    PRIVATE "${VCPKG_INSTALLED_DIR}/${VCPKG_TARGET_TRIPLET}/include"
)
target_link_libraries(base64 PRIVATE fmt::fmt)        # fmt库
# target_link_libraries(base64 PRIVATE cppcodec) 纯头文件库不需要链接
# 像这么路径写死也不太好
# target_include_directories(base64 PRIVATE /home/abin/workspace/vcpkgDemo/build/vcpkg-linux-debug/vcpkg_installed/x64-linux/include)
