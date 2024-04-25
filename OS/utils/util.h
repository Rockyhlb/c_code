#ifndef _Util_
#define _Util_

// 实现密码隐藏的函数   
void hide_password(char *password);

// 根据当前路径找到，根据‘/’分割后获取到最后一个路径，用于控制台实时打印当前路径
char *find_last_path(char *path);

#endif