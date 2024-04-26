#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "util.h"

#include <time.h>
#include "file.h"

// 初始化文件系统
void init_file_system(FILEHASH *root) {
    for(int i = 0; i < HASH_SIZE; i++)
		root->buckets[i] = NULL;
    // 创建根目录
    File root_file;
    strcpy(root_file.name, "/");
    root_file.type = DIRECTORY;
    strcpy(root_file.owner_id, "root");
    strcpy(root_file.group_id, "root");
    root_file.size = 0;

    // 获取当前时间
	struct tm cur_time = get_cur_time();

    root_file.month = cur_time.tm_mon;
    root_file.day = cur_time.tm_mday;

    strcpy(root_file.time_str, "");
    file_put(root, "/", root_file);
}

// 计算键的哈希值
unsigned int hash(const char *key) {
    unsigned int hashval = 0;
    for (; *key != '\0'; key++) {
        hashval = *key + (hashval << 5) - hashval;
    }
    return hashval % HASH_SIZE;
}

// 在哈希表中查找文件
File* file_get(FILEHASH* root, const char *key) {
    unsigned int hashval = hash(key);
    HashNode* node = root->buckets[hashval];
    while (node != NULL) {
        if (strcmp(node->key, key) == 0) {
            return &(node->value); // 文件找到，返回文件的元数据或内容
        }
        node = node->next;
    }
    return NULL; // 文件不存在
}

// 向哈希表中插入文件
void file_put(FILEHASH *root, const char *key, File value) {
    unsigned int hashval = hash(key) % HASH_SIZE;
    HashNode* node = root->buckets[hashval];
    // 检查键是否已经存在，如果存在则更新值
    while (node != NULL) {
        if (strcmp(node->key, key) == 0) {
            node->value = value;
            return;
        }
        node = node->next;
    }
    // 创建新节点并插入到链表头部
    HashNode* new_node = (HashNode*)malloc(sizeof(HashNode));
    if (new_node == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return;
    }
    strcpy(new_node->key, key);
    new_node->value = value;
    new_node->next = root->buckets[hashval];
    root->buckets[hashval] = new_node;
}

// 根据当前路径遍历文件
void file_show_cur(FILEHASH* root, char *path) {
    HashNode *current_node;
    char current_path[CUR_MAX_PATH] = "";

    // 如果路径为空，则从根目录开始
    if (strlen(path) == 0) {
        strcpy(current_path, "/");
    } else {
        strcpy(current_path, path);
    }

    // 获取当前路径的文件节点
    char cur_dir[60];
    find_last_path(path,cur_dir);
    current_node = file_get_by_key(root, current_path);

    // 检查当前文件类型是否为目录
    if (current_node == NULL || current_node->value.type != DIRECTORY) {
        printf("Invalid directory.\n");
        return;
    }

    // 输出当前目录下的文件列表
    printf("Files in directory '%s':\n", current_path);

    current_node = current_node->next;
    while (current_node != NULL) {
        printf("%s\n", current_node->key);
        current_node = current_node->next;
    }
}

char *file_cd_path(FILEHASH *fileHash, char *cur_path) {
    // 检查当前路径是否已经是根目录
    if (strcmp(cur_path, "/") == 0) {
        printf("Already at root directory.\n");
        return cur_path;
    }

    // 寻找最后一个斜杠的位置
    char *last_slash = strrchr(cur_path, '/');
    if (last_slash == NULL) {
        printf("Invalid path.\n");
        return cur_path;
    }

    // 将最后一个斜杠替换为结束符，即移动到父目录
    *last_slash = '\0';

    // 返回移动后的路径
    return cur_path;
}

// 在Hash表中根据key获取链表头节点
File *file_get_by_key(FILEHASH *root, const char *key) {
    unsigned int hashval = hash(key) % HASH_SIZE;
    HashNode *node = root->buckets[hashval];
    while (node != NULL) {
        if (strcmp(node->key, key) == 0) {
            return &(node->value); // 返回文件的元数据或内容
        }
        node = node->next;
    }
    return NULL; // 文件不存在
}