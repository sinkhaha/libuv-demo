#include <stdio.h>
#include <uv.h> // 引入libuv头文件

void prep_cb(uv_prepare_t *handle) {
    printf("prepare callback\n");
}

int main() {
    uv_prepare_t prep;

    // 初始化 prepare handle
    uv_prepare_init(uv_default_loop(), &prep);

    // 启动prepare，prep_cb 为事件循环都会执行的回调函数 
    uv_prepare_start(&prep, prep_cb);

    // 执行事件循环，运行模式为UV_RUN_DEFAULT，在 prepare阶段 会执行 prep_cb 回滴
    uv_run(uv_default_loop(), UV_RUN_DEFAULT);

    return 0;
}
