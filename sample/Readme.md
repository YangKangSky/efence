sample1: 可执行文件中malloc访问越界



sample2：动态库中malloc访问越界，运行时打桩



sample3：动态库中malloc访问越界，链接时打桩。方式3，不能立马发现错误，需要在free时才发现异常。



sample4：动态库中malloc访问越界，链接时打桩，但是调试库需要静态链接到需要debug的动态库中

