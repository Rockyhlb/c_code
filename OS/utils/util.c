#include <stdio.h>
#include <stdlib.h>
#include "util.h"

#include <termios.h>
#include <unistd.h>

// 限制用户名和密码长度
#define USERNAME_MAX_LENGTH 20
#define PASSWORD_MAX_LENGTH 25

// 实现密码隐藏的函数
void hide_password(char *password) {
    struct termios old, new;
    tcgetattr(fileno(stdin), &old);
    new = old;
    new.c_lflag &= ~ECHO; // 关闭回显
    tcsetattr(fileno(stdin), TCSANOW, &new);
    fgets(password, PASSWORD_MAX_LENGTH, stdin);
    // 去除输入字符串末尾的换行符
    password[strcspn(password, "\n")] = '\0';
    tcsetattr(fileno(stdin), TCSANOW, &old);
}

// 根据当前路径找到，根据‘/’分割后获取到最后一个路径，用于控制台实时打印当前路径  比如：[root@myOS root]#
char *find_last_path(char *path) {
    // 遍历字符数组找到最后一个路径
    int i;
    int last_path_start = 0;
    int last_path_end = 0;

    for (i = 0; path[i] != '\0'; i++) {
        if (path[i] == '/') {
            last_path_start = i + 1; // 记录路径的起始位置
        }
    }

    // 最后一个路径的结束位置是字符串的结束符
    last_path_end = i;

    // // 输出最后一个路径
    // char res[20]; // 静态数组以便返回局部变量的地址
    // res[0] = '\0';       // 确保字符串为空
    // for (i = last_path_start; i < last_path_end; i++) {
    //     strcat(res, &path[i]);
    // }
    // return res;
    
    // 从路径中提取最后一个路径
    static char res[20]; // 静态数组用于存储结果，需要静态是因为需要在函数外部返回该数组的指针
    int j = 0;
    for (i = last_path_start; i < last_path_end; i++) {
        res[j++] = path[i];
    }
    res[j] = '\0'; // 添加字符串结束符
    return res;
}