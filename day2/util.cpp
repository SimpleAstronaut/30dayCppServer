// 学习30天cpp服务器学习代码
// day2-异常处理封装函数
// auther: SimpleAstronaut
// time: 2022-10-16

#include "util.h"
#include <stdio.h>
#include <stdlib.h>

void errif(bool condition, const char *errmsg){
    if(condition){
        perror(errmsg);
        exit(EXIT_FAILURE);
    }
}
//原作者注释：第一个参数是是否发生错误，如果为真，则
//表示有错误发生，会调用<stdio.h>头文件中的perror，
//这个函数会打印出errno的实际意义，还会打印出我们传
//入的字符串，也就是第函数第二个参数，让我们很方便定
//位到程序出现错误的地方。然后使用<stdlib.h>中的exit
//函数让程序退出并返回一个预定义常量EXIT_FAILURE。
