/**
 * 简易数据库
 */
#ifndef CHAT_DB_H
#define CAHT_DB_H

#include <stdio.h>
#include <string.h>

#define CHAT_DB "chat_db.dat"
#define LINE_SIZE 1024

struct entry {
    int col;
    char *key;
    char *value;
};

// 打开文件
extern FILE *open_db(char *mode);

// 根据元素获取记录, -1返回错误
extern int fetch_record(struct entry elem, char* res_record);

// 根据主键获取记录
extern char *fetch_record_by_id(char *id);

// 存储记录
extern void store_record(char *record);

// 删除记录
extern void del_record(char *id);

#endif