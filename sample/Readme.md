## sample1: 

是一个可执行文件中malloc内存访问越界的用例，包含4种情况。

1. s1_eftest_static: 静态链接libefence.a和libcallstacklogger.a以及libbacktrace.a
2. s1_eftest_wrapper_static: 会修改可执行文件中的malloc调用修改为__wrap_malloc函数。并不会影响到其他库和obj文件中的符号。静态链接libefence_wrapper.a 和libcallstacklogger.a以及libbacktrace.a
3. s1_eftest_wrapper_share：链接libefence_wrapper.so,  以及libcallstacklogger.a以及libbacktrace.a中的所有符号。(亦或另外一种方案，把libcallstacklogger.a以及libbacktrace.a中的符号全部打包到s1_eftest_wrapper_share)
4. s1_eftest_share：动态链接libefence.so, 静态链接libcallstacklogger.a以及libbacktrace.a



以上4种情况，运行时efence均可以在异常发生时，即刻检测到，并触发crash.



## sample2：

是动态库MemoryOverrun中的一个函数malloc访问越界，运行时打桩。打桩方式包括如下2种。

1. s2_test：运行时打桩，通过LD_PRELOAD的方式，替换可执行文件中的内存操作函数。

```
LD_PRELOAD=./libefence.so  ./test
```
由于需要在当前路径查找MemoryOverrun库，所以命令修改为

```
LD_LIBRARY_PATH=$LD_LIBRARY_PATH:.  LD_PRELOAD=./libefence.so  ./test
```



2. s2_test_wrapper_share：构建过程中的链接阶段打桩。替换

为了避免使用LD_PRELOAD替换内存操作函数，可以在链接MemoryOverrun库时，wrap修改该库里面的内存操作函数。

s2_test_wrapper_share依赖libMemoryOverrun_wrap.so，libMemoryOverrun_wrap.so依赖libefence_wrapper.so，且以及libcallstacklogger.a以及libbacktrace.a中的所有符号都放入到libMemoryOverrun.so中。

```
./s2_test_wrapper_share 
```

执行方式。





## sample3：

动态库中malloc访问越界，链接时打桩。方式3，不能立马发现错误，需要在free时才发现异常。









## sample4：

动态库中malloc访问越界，链接时打桩，但是调试库需要静态链接到需要debug的动态库中





























