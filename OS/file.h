#ifndef _FILEHASH_
#define _FILEHASH_

// 选择一个适当的素数作为哈希表大小
#define HASH_SIZE 101
#define CUR_MAX_PATH 100

// 文件类型
enum FileType {
    COMMONFILE,
    DIRECTORY,
    SYMLINK,
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
    char owner_id[20]; // 所有者 ID
    char group_id[20]; // 所属组 ID
    long size; // 文件大小（字节）
    int month;
    int day;
    char time_str[20];  // 时:分
}File;

// 哈希表的节点结构
typedef struct HashNode {
    char key[256]; // 键（文件名）
    File value; // 值（文件的元数据或内容）
    struct HashNode* next; // 下一个节点指针（解决哈希冲突）
} HashNode;

// 哈希表结构
#define MAX_FILES 100 // 最大文件数
typedef struct {
    HashNode *buckets[MAX_FILES]; // 指针数组
} FILEHASH;

// 初始化文件系统
void init_file_system(FILEHASH *root);

// 在哈希表中查找文件
File *file_get(FILEHASH* root, const char *key);

// 向哈希表中插入文件
void file_put(FILEHASH *root, const char *key, File value);

// 根据当前路径遍历文件
void file_show_cur(FILEHASH* root, char *path);

// cd /绝对
char *file_cd_path(FILEHASH *fileHash, char *cur_path);

// 在Hash表中根据key获取链表头节点
File *file_get_by_key(FILEHASH *root, const char *key);

#endif