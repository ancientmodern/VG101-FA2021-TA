#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "database.h"

void execute(Database *, char *);

Table *getTable(Database *db, char *tableName) {
    for (int i = 0; i < db->tableNum; ++i) {
        if (!strcmp(db->tables[i].name, tableName)) {
            return &(db->tables[i]);
        }
    }
    return NULL;
}

int ascendDeadline(const void *lhs, const void *rhs) {
    return (*(Assignment *) lhs).deadline - (*(Assignment *) rhs).deadline;
}

int descendDifficulty(const void *lhs, const void *rhs) {
    return (*(Assignment *) rhs).difficulty - (*(Assignment *) lhs).difficulty;
}

int alphaTableName(const void *lhs, const void *rhs) {
    return strcmp((char *) lhs, (char *) rhs);
}

void insert(Table *tb, char *course, char *name, int ddl, int diff) {
    Assignment *assign = &tb->assignments[tb->assignNum++];
    strcpy(assign->course, course);
    strcpy(assign->name, name);
    assign->deadline = ddl;
    assign->difficulty = diff;
}

int update(Table *tb, char *key, char *value, char *course, char *name) {
    int count = 0;
    for (int i = 0; i < tb->assignNum; ++i) {
        Assignment *assign = &tb->assignments[i];
        if ((course[0] == '*' || !strcmp(assign->course, course)) && (name[0] == '*' || !strcmp(assign->name, name))) {
            ++count;
            if (!strcmp(key, "course")) {
                strcpy(assign->course, value);
            } else if (!strcmp(key, "name")) {
                strcpy(assign->name, value);
            } else if (!strcmp(key, "deadline")) {
                assign->deadline = strtol(value, NULL, 10);
            } else if (!strcmp(key, "difficulty")) {
                assign->difficulty = strtol(value, NULL, 10);
            }
        }
    }
    return count;
}

int delete(Table *tb, char *course, char *name) {
    int count = 0;
    for (int i = 0; i < tb->assignNum; ++i) {
        Assignment *assign = &tb->assignments[i];
        if ((course[0] == '*' || !strcmp(assign->course, course)) && (name[0] == '*' || !strcmp(assign->name, name))) {
            ++count;
            for (int j = i; j < tb->assignNum - 1; ++j) {
                tb->assignments[j] = tb->assignments[j + 1];
            }
            tb->assignNum--;
            --i;
        }
    }
    return count;
}

void my_select(Table *tb, char *course, char *name, char *sort, char *limit) {
    if (!strcmp(sort, "deadline")) {
        qsort(tb->assignments, tb->assignNum, sizeof(Assignment), ascendDeadline);
    } else {
        qsort(tb->assignments, tb->assignNum, sizeof(Assignment), descendDifficulty);
    }
    int count = 0, upper = strtol(limit, NULL, 10);
    for (int i = 0; i < tb->assignNum; ++i) {
        Assignment *assign = &tb->assignments[i];
        if ((course[0] == '*' || !strcmp(assign->course, course)) && (name[0] == '*' || !strcmp(assign->name, name))) {
            if (count++ >= upper) {
                break;
            }
            printf("%s %s %d %d\n", assign->course, assign->name, assign->deadline, assign->difficulty);
        }
    }
}

void loadTable(Database *db, const char *filename) {
    FILE *fp = fopen(filename, "r");
    Table *tb = &db->tables[db->tableNum++];
    tb->assignNum = 0;
    char course[MAX_NAME], name[MAX_NAME];
    int ddl, diff;
    fscanf(fp, "%s", course);
    strcpy(tb->name, course);
    while (fscanf(fp, "%s %s %d %d", course, name, &ddl, &diff) != EOF) {
        insert(tb, course, name, ddl, diff);
    }
    fclose(fp);
}

void saveTable(Table *tb, const char *filename) {
    FILE *fp = fopen(filename, "w");
    fprintf(fp, "%s\n", tb->name);
    qsort(tb->assignments, tb->assignNum, sizeof(Assignment), ascendDeadline);
    for (int i = 0; i < tb->assignNum; ++i) {
        Assignment *temp = &tb->assignments[i];
        fprintf(fp, "%s %s %d %d\n", temp->course, temp->name, temp->deadline, temp->difficulty);
    }
    fclose(fp);
}

void printTable(Table *tb) {
    printf("%s\n", tb->name);
    printf("Course Name Deadline Difficulty\n");
    qsort(tb->assignments, tb->assignNum, sizeof(Assignment), ascendDeadline);
    for (int i = 0; i < tb->assignNum; ++i) {
        Assignment *temp = &tb->assignments[i];
        printf("%s %s %d %d\n", temp->course, temp->name, temp->deadline, temp->difficulty);
    }
}

void listTable(Database *db) {
    char names[MAX_TABLE][MAX_NAME] = {{0}};
    for (int i = 0; i < db->tableNum; ++i) {
        strcpy(names[i], db->tables[i].name);
    }
    qsort(names, db->tableNum, sizeof(names[0]), alphaTableName);
    for (int i = 0; i < db->tableNum; ++i) {
        printf("%s\n", names[i]);
    }
}

void autoTable(Database *db, char *filename) {
    char line[MAX_LINE];
    FILE *fp = fopen(filename, "r");
    while (fgets(line, MAX_LINE, fp)) {
        execute(db, line);
    }
    fclose(fp);
}

void execute(Database *db, char str[]) {
    if (str[strlen(str) - 1] == '\n') {
        str[strlen(str) - 1] = 0;
    }

    char argv[25][MAX_NAME] = {{0}};
    size_t index = 0;
    char *token = strtok(str, " ");
    while (token != NULL) {
        strcpy(argv[index++], token);
        token = strtok(NULL, " ");
    }

    if (!strcmp(argv[0], "LOAD")) {
        loadTable(db, argv[1]);
        printf("LOAD: success\n");
    } else if (!strcmp(argv[0], "SAVE")) {
        saveTable(getTable(db, argv[1]), argv[2]);
        printf("SAVE: success\n");
    } else if (!strcmp(argv[0], "PRINT")) {
        printTable(getTable(db, argv[1]));
    } else if (!strcmp(argv[0], "LIST")) {
        listTable(db);
    } else if (!strcmp(argv[0], "AUTO")) {
        autoTable(db, argv[1]);
    } else if (!strcmp(argv[0], "INSERT")) {
        int ddl, diff;
        ddl = strtol(argv[4], NULL, 10);
        diff = strtol(argv[5], NULL, 10);
        insert(getTable(db, argv[7]), argv[2], argv[3], ddl, diff);
        printf("INSERT: success\n");
    } else if (!strcmp(argv[0], "UPDATE")) {
        int count = update(getTable(db, argv[5]), argv[2], argv[3], argv[7], argv[8]);
        printf("UPDATE: update %d records\n", count);
    } else if (!strcmp(argv[0], "DELETE")) {
        int count = delete(getTable(db, argv[1]), argv[3], argv[4]);
        printf("DELETE: delete %d records\n", count);
    } else if (!strcmp(argv[0], "SELECT")) {
        my_select(getTable(db, argv[1]), argv[3], argv[4], argv[7], argv[9]);
    }
}

int main() {
    Database db = {.tableNum = 0};
    char line[MAX_LINE];
    while (fgets(line, MAX_LINE, stdin)) {
        if (!strcmp(line, "EXIT\n")) {
            printf("Exit the Deadline Database! Hope you have already conquered all deadlines!\n");
            break;
        }
        execute(&db, line);
    }
    // printf("%llu %llu %llu\n", sizeof(Database), sizeof(Table), sizeof(Assignment));
    return 0;
}
