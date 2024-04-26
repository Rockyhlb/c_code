#ifndef _Util_
#define _Util_

#include "file.h"

// 限制用户名和密码长度
#define USERNAME_MAX_LENGTH 20
#define PASSWORD_MAX_LENGTH 25

// 实现密码隐藏的函数   
void hide_password(char *password);

// 验证登陆用户
int verify_user(FILEHASH *fileHash,char *username,char *password);

// 获取时间
struct tm get_cur_time();

// 根据当前路径找到，根据‘/’分割后获取到最后一个路径，用于控制台实时打印当前路径
void *find_last_path(const char *path,char *last_path);

void file_cd_front(char *cur_path,const char *del_path);

#endif