# 定时器的使用

## 编译libuv
> 以下为mac平台执行

1. 下载libuv源码

```
git clone https://github.com/libuv/libuv.git
```

2. 下载完进入libuv，进行编译，按照[文档]( https://github.com/libuv/libuv/tree/v1.44.2)，如执行以下命令

```bash
$ sh autogen.sh
$ ./configure
$ make
$ make check
$ make install
```
3. 完成后，查看本地 `/usr/local/include/` 目录是否有`uv.h` 和 `uv` 等头文件，存在即正常

```bash
~ cd /usr/local/include
~ ls | grep uv
uv
uv.h
```

4. 完成后，查看本地 `/usr/local/lib/` 目录是否存在`libuv.a`静态链接库文件，存在即正常
```bash
~ cd /usr/local/lib
~ ls | grep libuv.a
libuv.a
```

## 使用libuv
> 这里以 cmake 构建工具为例

1. 新建 `timer` 项目

2. 新建 `main.c` 文件

   ```c
   #include <stdio.h>
   #include <uv.h> // 引入libuv头文件
   
   void once_cb(uv_timer_t *handle) {
       printf("timer callback\n");
   }
   
   int main() {
       uv_timer_t once;
       // 初始化 uv_timer_t 结构体
       uv_timer_init(uv_default_loop(), &once);
   
       // 启动定时器，超时后执行 once_cb回调函数，2000为超时时间，0 表示只执行一次回调
       uv_timer_start(&once, once_cb, 2000, 0);
   
       // 执行事件循环
       uv_run(uv_default_loop(), UV_RUN_DEFAULT);
   
       return 0;        
   }
   ```

3. 把编译好的`libuv`的头文件和静态链接库复制到项目中（具体看`CMakeLists.txt`中配置的头文件和静态链接库搜索路径）

   * 新建`include`目录，存放头文件，把`/usr/local/include`下的`uv`文件夹和`uv.h`文件复制过去
   * 新建`lib` 目录，存放链接库文件，把`/usr/local/lib`下的`libuv.a`复制过去

4. 新建`CMakeLists.txt`

   ```txt
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
   ```

5. 新建`build`文件夹（存放编译后的产物），并编译生成可执行文件

   ```bash
   cd build
   cmake ../ # 在build目录生成Makefile等配置文件，要在 CMakeLists.txt 所在目录执行
   make # 根据生成makefile文件，编译程序，生成可执行文件
   ```

6. 最后在 `build` 目录生成 `bin/main`可执行文件

7. 执行 `main` 可执行文件即可

   ```bash
   # 执行main文件
   ./bin/main 
   
   # 输出timer callback
   ```

   

