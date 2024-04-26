#include <stdio.h>
#include <stdlib.h>
#include "util.h"

#include <termios.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

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

// 验证登陆用户
int verify_user(FILEHASH *fileHash,char *username,char *password) {
	if (0 == strcmp(username,"root") && 0 == strcmp(password,"00")) {
		File *root_dir = file_get(fileHash, "/");
		if (root_dir == NULL) {
			// 如果根目录不存在，则创建根目录
			File root_file;
			strcpy(root_file.name, username);
			root_file.type = DIRECTORY;
            strcpy(root_file.owner_id, username);
            strcpy(root_file.group_id, username);
			root_file.size = 0;

            struct tm cur_time = get_cur_time();

			root_file.month = cur_time.tm_mon;
			root_file.day = cur_time.tm_mday;

			sprintf(root_file.time_str, "%02d:%02d", cur_time.tm_hour, cur_time.tm_min);
			file_put(fileHash, "/", root_file);
		}
		return 0;
	}
    return -1;
}

struct tm get_cur_time() {
    // 获取当前时间
    time_t current_time;
    struct tm *local_time;

    current_time = time(NULL);
    local_time = localtime(&current_time);
    return *local_time;
}

// 根据当前路径找到，根据‘/’分割后获取到最后一个路径，用于控制台实时打印当前路径  比如：[root@myOS root]#
void *find_last_path(const char *path,char *last_path) {
    // 当前路径已经是根目录时
    if(strcmp(path,"/") == 0) {
        strcpy(last_path,"/");
        return;
    }
    // 遍历字符数组找到最后一个路径的起始位置
    int i;
    int last_path_start = 0;
    for (i = 0; path[i] != '\0'; i++) {
        if (path[i] == '/') {
            last_path_start = i + 1; // 记录路径的起始位置
        }
    }

    // 从路径中提取最后一个路径并存储到指定的缓冲区中
    int j = 0;
    for (i = last_path_start; path[i] != '\0'; i++) {
        last_path[j++] = path[i];
    }
    last_path[j] = '\0'; // 添加字符串结束符
}

// 从字符串cur_path中删除字符串 del_path
void file_cd_front(char *cur_path,const char *del_path) {
    // 找到 last_path 在 cur_path 中的起始位置
    char *last_path_start = strstr(cur_path, del_path);
    if (last_path_start != NULL) {
        // 找到 del_path 的前一个斜杠的位置
        char *prev_slash = strrchr(cur_path, '/');
        if (prev_slash != NULL) {
            // 将 prev_slash 后面的字符全部替换为字符串结束符 '\0'，即移除 del_path
            *prev_slash = '\0';
        }
    }
}