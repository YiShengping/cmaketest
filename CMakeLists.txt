cmake_minimum_required(VERSION 3.10)
project(MyProject)

# 设置 pciutils 库路径
set(PCI_LIBRARY "${CMAKE_CURRENT_SOURCE_DIR}/../pciutils-3.13.0/lib/libpci.a")
set(PCI_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../pciutils-3.13.0/lib")

# 添加可执行文件
add_executable(main main.cpp)

# 设置编译选项
set_target_properties(main PROPERTIES
    CXX_STANDARD 11
    CXX_STANDARD_REQUIRED ON
)

# 设置包含目录
target_include_directories(main PRIVATE ${PCI_INCLUDE_DIR})

# 链接静态库和依赖库
target_link_libraries(main PRIVATE ${PCI_LIBRARY} z dl pthread)
