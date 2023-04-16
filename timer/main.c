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
