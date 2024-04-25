#ifndef _File_
#define _File_

// 文件类型
enum FileType {
    COMMONFILE,
    DIRECTORY,
    SYMLINK,
    // 其他类型可以根据需要添加
};

// 文件权限
struct Permissions {
    int owner_read;
    int owner_write;
    int owner_execute;
    int group_read;
    int group_write;
    int group_execute;
    int others_read;
    int others_write;
    int others_execute;
};

// 文件信息结构体
typedef struct {
    char name[256]; // 文件名
    enum FileType type; // 文件类型
    struct Permissions permissions; // 文件权限
    int owner_id; // 所有者 ID
    int group_id; // 所属组 ID
    long size; // 文件大小（字节）
    int month;
    int day;
    char time_str[10];  // 时:分
}File;

// 初始化文件系统
void initFileSystem(File *root);

#endif