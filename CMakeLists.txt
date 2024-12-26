cmake_minimum_required(VERSION 3.10)
project(pci_test)

# 设置C标准
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# 设置pciutils源码路径
set(PCIUTILS_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../pciutils-3.13.0)

# 添加pciutils库源文件
set(PCIUTILS_SOURCES
    ${PCIUTILS_SOURCE_DIR}/lib/init.c
    ${PCIUTILS_SOURCE_DIR}/lib/access.c
    ${PCIUTILS_SOURCE_DIR}/lib/generic.c
    ${PCIUTILS_SOURCE_DIR}/lib/dump.c
    ${PCIUTILS_SOURCE_DIR}/lib/names.c
    ${PCIUTILS_SOURCE_DIR}/lib/filter.c
    ${PCIUTILS_SOURCE_DIR}/lib/names-hash.c
    ${PCIUTILS_SOURCE_DIR}/lib/names-parse.c
    ${PCIUTILS_SOURCE_DIR}/lib/names-net.c
    ${PCIUTILS_SOURCE_DIR}/lib/names-cache.c
    ${PCIUTILS_SOURCE_DIR}/lib/params.c
    ${PCIUTILS_SOURCE_DIR}/lib/caps.c
    ${PCIUTILS_SOURCE_DIR}/lib/win32-cfgmgr32.c
    ${PCIUTILS_SOURCE_DIR}/lib/win32-helpers.c
    ${PCIUTILS_SOURCE_DIR}/lib/win32-sysdbg.c
    ${PCIUTILS_SOURCE_DIR}/lib/i386-ports.c
    ${PCIUTILS_SOURCE_DIR}/lib/emulated.c
    ${PCIUTILS_SOURCE_DIR}/lib/names-hwdb.c
)

# 创建pciutils静态库
add_library(pciutils STATIC ${PCIUTILS_SOURCES})

# 设置包含目录
target_include_directories(pciutils PUBLIC 
    ${PCIUTILS_SOURCE_DIR}/lib
    ${PCIUTILS_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}  # 添加当前目录以包含config.h
)

# Windows特定设置
if(WIN32)
    target_link_libraries(pciutils PUBLIC setupapi cfgmgr32)
    target_compile_definitions(pciutils PRIVATE PCI_OS_WINDOWS)
    target_compile_definitions(pciutils PRIVATE WIN32_LEAN_AND_MEAN)
endif()

# 添加可执行文件
add_executable(pci_test src/main.c)

# 链接库
target_link_libraries(pci_test PRIVATE pciutils)
