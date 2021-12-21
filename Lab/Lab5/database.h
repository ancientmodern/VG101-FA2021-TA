//
// Created by ancientmodern on 2021/11/5.
//

#ifndef LAB_5_DATABASE_H
#define LAB_5_DATABASE_H

#define MAX_LINE 120
#define MAX_NAME 15
#define MAX_ASSIGNMENT 100
#define MAX_TABLE 10

typedef struct {           // Example:
    char course[MAX_NAME]; // "vg101"
    char name[MAX_NAME];   // "lab5"
    int deadline;          // 20211115
    int difficulty;        // 100
} Assignment;

typedef struct {
    char name[MAX_NAME];
    int assignNum;
    Assignment assignments[MAX_ASSIGNMENT];
} Table;

typedef struct {
    int tableNum;
    Table tables[MAX_TABLE];
} Database;

#endif //LAB_5_DATABASE_H