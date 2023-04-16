cmake_minimum_required(VERSION 3.0.0)
project(main VERSION 0.1.0) # 指定工程名字为 main

include(CTest)
enable_testing()

# 定义工程根目录，CMAKE_SOURCE_DIR为内建变量，表示工程根目录的CMakeLists.txt文件路径
set(ROOT_DIR ${CMAKE_SOURCE_DIR})

# 指定引用的外部库的搜索路径，这里把libuv的libuv.a静态链接库复制过来了
link_directories(${ROOT_DIR}/lib)
# link_directories(/usr/local/lib) # 默认libuv编译后链接库是存在在这个目录

# 指定头文件搜索路径，这里把libuv的头文件复制过来了
INCLUDE_DIRECTORIES(${ROOT_DIR}/include)
# INCLUDE_DIRECTORIES(/usr/local/include)  # 默认libuv编译后头文件是存在在这个目录

# 指定可执行文件存放目录 build下的bin目录
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

add_executable(${PROJECT_NAME} main.c) # 构建可执行程序

# 使用 libuv.a 静态链接库
target_link_libraries(${PROJECT_NAME} libuv.a)
