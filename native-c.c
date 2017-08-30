#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

#define INSERT_COUNT         1000
#define COMMAND_TABLE_CREATE "CREATE TABLE COMPANY(ID INT PRIMARY KEY NOT NULL, NAME TEXT NOT NULL);"
#define COMMAND_TRANSACTION  "BEGIN TRANSACTION;"
#define COMMAND_COMMIT       "COMMIT;"

enum {
    ACTION_INSERT = 0,
    ACTION_SELECT,
    ACTION_BOTH
};

// callback
static int callback(void *unused, int argc, char *argv[], char **col) {
    return 0;
}

int main(int argc, char *argv[]) {
    int i = 0, l = 0, count = 0, action = 0;
    char *cmd = NULL, *err = NULL;
    sqlite3 *db = NULL;

    // get rep count
    if (argc > 1) {
        count = atoi(argv[1]);
    } else {
        count = INSERT_COUNT;
    }

    // insert/select/both
    if (argc > 2) {
        action = atoi(argv[2]);
    }

    // allocate command
    cmd = (char *)malloc(sizeof(char) * ((38 * count) + 1));

    // connect db
    if (sqlite3_open("native-c.db", &db) != 0) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);

        return 1;
    }

    if (action == ACTION_INSERT || action == ACTION_BOTH) {
        // begin transaction
        if (sqlite3_exec(db, COMMAND_TRANSACTION, callback, 0, &err) != 0) {
            fprintf(stderr, "SQL error: %s\n", err);
            sqlite3_free(err);

            return 1;
        }

        // create table
        if (sqlite3_exec(db, COMMAND_TABLE_CREATE, callback, 0, &err) != 0) {
            fprintf(stderr, "SQL error: %s\n", err);
            sqlite3_free(err);

            return 1;
        }

        // inserts
        for (i = 0, l = count; i < l; i += 1) {
            sprintf(cmd, "INSERT INTO COMPANY VALUES (%d, %d);", i, i);

            if (sqlite3_exec(db, cmd, callback, 0, &err) != 0) {
                fprintf(stderr, "SQL error: %s\n", err);
                sqlite3_free(err);

                return 1;
            }
        }

        // commit inserts
        if (sqlite3_exec(db, COMMAND_COMMIT, callback, 0, &err) != 0) {
            fprintf(stderr, "SQL error: %s\n", err);
            sqlite3_free(err);

            return 1;
        }
    }

    if (action == ACTION_SELECT || action == ACTION_BOTH) {
        // selects
        for (i = 0, l = count; i < l; i += 1) {
            sprintf(cmd, "SELECT * FROM COMPANY WHERE ID=%d;", i);

            if (sqlite3_exec(db, cmd, callback, 0, &err) != 0) {
                fprintf(stderr, "SQL error: %s\n", err);
                sqlite3_free(err);

                return 1;
            }
        }
    }

    // close db
    sqlite3_close(db);

    return 0;
}
