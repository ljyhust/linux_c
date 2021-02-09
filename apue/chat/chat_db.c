#include "chat_db.h"

FILE *open_db(char *mode) {
    return fopen(CHAT_DB, mode);
}

int fetch_record(struct entry elem, char* res_record) {
    FILE *fi = open_db("r");
    char buff[LINE_SIZE];
    int i;
    char *line = NULL;
    while ((fgets(buff, LINE_SIZE, fi)) != NULL)
    {
        for(i = 0; i < elem.col; i++) {
            line = strtok(buff, ":");
        }
        if (strcmp(line, elem.value) == 0) {
            strcpy(res_record, buff);
            fclose(fi);
            return 0;
        }
    }
    fclose(fi);
    return -1;
}

char *fetch_record_by_id(char *id) {

}

// 存储记录
void store_record(char *record) {
    FILE *fo = open_db("a");
    fputs(record, fo);
    fputs("\n", fo);
    fclose(fo);
}

// 删除记录
void del_record(char *id) {

}