#include "chat_db.h"
#include <stdlib.h>

int main(int argc, char *argv[]) {
    char *test = "ljy:ljyhust:line";
    store_record(test);

    struct entry test_entry;
    test_entry.col = 1;
    test_entry.value = "ljy";
    char *res;
    fetch_record(test_entry, res);
    printf("result %s\n", res);
    exit(0);
}