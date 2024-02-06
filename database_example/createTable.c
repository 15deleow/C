#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include "sqlite/sqlite3.h"

static int callback(void * notUsed, int argc, char **argv, char **azColName){
    int i;
    for(i = 0; i < argc; i++){
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return 0;
}

int main(int argc, char* argv[]) {
    sqlite3 * db;
    char *zErrMsg = 0;
    int rc;
    char *sql;

    /* Open the database */
    rc = sqlite3_open("test.db", &db);
    if(rc){
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        return(EXIT_FAILURE);
    }else{
        fprintf(stdout, "Opened database successfully\n");
    }

    /* Create SQL Statement*/
    sql = "Create TABLE COMPANY(" \
        "ID INT PRIMARY KEY         NOT NULL," \
        "NAME           TEXT        NOT NULL," \
        "AGE            INT         NOT NULL," \
        "ADDRESS        CHAR(50),"\
        "SALARY         REAL );";

    /* Execute SQL Statement*/
    rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);

    if(rc != SQLITE_OK){
        fprintf(stderr, "SQL Error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } else{
        fprintf(stdout, "Table Created succssfully\n");
    }

    /*Close the database*/
    sqlite3_close(db);

    return EXIT_SUCCESS;
}