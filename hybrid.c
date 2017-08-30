#include <stdio.h>
#include <sqlite3.h>

#define COMMAND_TRANSACTION "BEGIN TRANSACTION;"
#define COMMAND_COMMIT      "COMMIT;"

static int callback(void *unused, int argc, char *argv[], char **col) {
    return 0;
}

void *connect(char *filename) {
    sqlite3 *db = NULL;

    if (sqlite3_open(filename, &db) != 0) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);

        return NULL;
    }

    return db;
}

void execute(void *db, char *cmd) {
    char *err = NULL;

    if (sqlite3_exec(db, cmd, callback, 0, &err) != 0) {
        fprintf(stderr, "SQL error: %s\n", err);
        sqlite3_free(err);
    }
}

void begin(void *db) {
    execute(db, COMMAND_TRANSACTION);
}

void commit(void *db) {
    execute(db, COMMAND_COMMIT);
}

void close(void *db) {
    sqlite3_close(db);
}
