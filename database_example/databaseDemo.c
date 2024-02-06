#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include "sqlite/sqlite3.h"

#define DATABASE "test.db"

enum actions{INSERT = 1, UPDATE, DELETE, SELECT, DISPLAY, EXIT };
enum boolean{TRUE = 1, FALSE = 0};

static long counter;

void clearScreen(void);
int openDatabase(char * filename, sqlite3 ** db);
int executeCommand(char * query, sqlite3 * db);

void clearScreen(void) {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

//Used to display data retrieved from database
static int callback(void * notUsed, int argc, char **argv, char **azColName){
    int i;
    for(i = 0; i < argc; i++){
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return 0;
}

static int deleteCallback(void * data, int argc, char **argv, char **azColName){
    int i;
    int *count = (int *)data;
    for(i = 0; i < argc; i++){
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");

    (*count)++;
    printf("count = %d\n", *count);
    return 0;
}

//Check if a certain entry exists in the database
int entryExists(char * name, sqlite3 *db){
    char selectSql[100];
    sprintf(selectSql, "SELECT 1 FROM COMPANY WHERE NAME='%s' LIMIT 1;", name);
    sqlite3_stmt *stmt;

    if (sqlite3_prepare_v2(db, selectSql, -1, &stmt, 0) != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        return -1; // Indicates an error
    }

    int result = FALSE;

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        result = TRUE; // Entry exists
    }

    sqlite3_finalize(stmt);
    return result;
}

//Inserts a new employee into company database
void insert(){
    char query[100];
    char name[10];
    char state[20];
    int id, age;
    float salary;

    sqlite3 * db;
    char *zErrMsg = 0;
    int rc;
    const char * data = "Callback function called";

    printf("Enter First Name of Employee: ");
    scanf("%s", name);
    printf("Enter age: ");
    scanf("%d", &age);
    printf("Enter State of Residency: ");
    scanf("%s", state);
    printf("Enter salary: ");
    scanf("%f", &salary);
    clearScreen();

    //Generate unique ID
    id = counter++;

    //Create sql statement
    sprintf(query, "INSERT INTO COMPANY (NAME, AGE, ADDRESS, SALARY) VALUES ('%s', %d, '%s', %f);", name, age, state, salary);

    //Open database
    if(openDatabase(DATABASE, &db) == FALSE){
        exit(EXIT_FAILURE);
    }

    //Exectute
    printf("CREATING ENTRY FOR NEW EMPLOYEE.... ");
    if(executeCommand(query, db) == FALSE){
        printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2 FAILED TO ADD ENTRY \xB2\xB2\xB2\xB2\xB2\xB2\xB2");
        exit(EXIT_FAILURE);
    }

    printf("ENTRY HAS BEEN ADDED TO DATABASE\n\n");
    
    /*Close the database*/
    sqlite3_close(db);

    printf("Press enter to continue...");
    getchar();
    getchar();
    clearScreen();

    return;
}

//Generates SQL command to create a database
void createTable(){
    sqlite3 *db;
    int rc = sqlite3_open(DATABASE, &db);
    if (rc == SQLITE_OK) {
        // Check if the table exists
        const char *checkQuery = "SELECT name FROM sqlite_master WHERE type='table' AND name='COMPANY';";
        sqlite3_stmt *checkStatement;

        if (sqlite3_prepare_v2(db, checkQuery, -1, &checkStatement, NULL) == SQLITE_OK) {
            if (sqlite3_step(checkStatement) != SQLITE_ROW) {
                // Table doesn't exist, create the database and table
                const char *createQuery = "CREATE TABLE COMPANY("
                                        "ID INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,"
                                        "NAME TEXT NOT NULL,"
                                        "AGE INT NOT NULL,"
                                        "ADDRESS CHAR(50),"
                                        "SALARY REAL );";
                if (sqlite3_exec(db, createQuery, NULL, NULL, NULL) != SQLITE_OK) {
                    fprintf(stderr, "Error creating table: %s\n", sqlite3_errmsg(db));
                }
            }

            sqlite3_finalize(checkStatement);
        } else {
            fprintf(stderr, "Error preparing statement: %s\n", sqlite3_errmsg(db));
        }

        sqlite3_close(db);
    } else {
        fprintf(stderr, "Error opening database: %s\n", sqlite3_errmsg(db));
    }
}

//Generates SQL Command to fetch records from database
void viewAll(){
    char * query = "SELECT * FROM COMPANY";
    sqlite3 * db;
    char *zErrMsg = 0;
    const char * data = "Callback function called";

    //Open database
    if(openDatabase(DATABASE, &db) == FALSE){
        exit(EXIT_FAILURE);
    }

    //Exectute
    printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2 EMPLOYEE ACCOUNT \xB2\xB2\xB2\xB2\xB2\xB2\xB2\n\n");
    if(executeCommand(query, db) == FALSE){
        printf("FAILED TO RETRIEVE ACCOUNT INFORMATION\n");
        exit(EXIT_FAILURE);
    }

    /*Close the database*/
    sqlite3_close(db);

    printf("Press enter to continue...");
    getchar();
    getchar();
    clearScreen();

    return;
}

//Display information of a certain account
void viewAccount(){
    char query[100];
    char name[30];
    sqlite3 * db;
    char *zErrMsg = 0;
    const char * data = "Callback function called";

    //Prompt user for name of employee
    printf("Enter Employee Name: ");
    scanf("%s", name);
    clearScreen();

    //Generate the query statement to get employee account info
    sprintf(query, "SELECT * FROM COMPANY WHERE NAME = '%s'", name);

    //Open database
    if(openDatabase(DATABASE, &db) == FALSE){
        exit(EXIT_FAILURE);
    }

    //Exectute query command
    printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2 EMPLOYEE ACCOUNT \xB2\xB2\xB2\xB2\xB2\xB2\xB2\n\n");
    if(executeCommand(query, db) == FALSE){
        printf("FAILED TO RETRIEVE ACCOUNT INFORMATION\n");
        exit(EXIT_FAILURE);
    }

    /*Close the database*/
    sqlite3_close(db);

    printf("Press enter to continue...");
    getchar();
    getchar();
    clearScreen();

    return;
}

void update(){
    char query[100];
    char name[10];
    int userChoice;
    sqlite3 * db;
    char *zErrMsg = 0;
    const char * data = "Callback function called";

    //Prompt User for what information to update
    printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2 UPDATE EMPLOYEE ACCOUNT \xB2\xB2\xB2\xB2\xB2\xB2\xB2");
    printf("\n\nEnter Name of Employee: ");
    scanf("%s", name);
    printf("\n1.Update Name\n2.Update Age\n3.Update Address\n4.Update Salary\n5.Exit\n\nEnter your choice: ");
    scanf("%d", &userChoice);
    switch(userChoice){
        case 1: {
            char * newName[15];
            printf("Enter new name: ");
            scanf("%s", newName);
            sprintf(query, "UPDATE COMPANY set NAME = '%s' where NAME= '%s'; ", newName, name);
            break;
        }
        case 2: {
            int age;
            printf("Enter new age: ");
            scanf("%d", &age);
            sprintf(query, "UPDATE COMPANY set AGE = %d where NAME= '%s'; ", age, name);
            break;
        }
        case 3: { 
            char * newAddress[30];
            printf("Enter new address: ");
            scanf("%s", newAddress);
            sprintf(query, "UPDATE COMPANY set ADDRESS = '%s' where NAME= '%s'; ", newAddress, name);
            break;
        }
        case 4: {
            float salary;
            printf("Enter new salary: ");
            scanf("%f", &salary);
            sprintf(query, "UPDATE COMPANY set SALARY = %f where NAME= '%s'; ", salary, name);
            break;
        }
        case 5: 
            return;
        default:
            printf("Invalid Input\n");
            return;
    }

    clearScreen();

    //Open database
    if(openDatabase(DATABASE, &db) == FALSE){
        exit(EXIT_FAILURE);
    }

    //Exectute
    printf("UPDATING EMPLOYEE ACCOUNT....");
    if(executeCommand(query, db) == FALSE){
        printf("FAILED TO UPDATE ACCOUNT\n");
        exit(EXIT_FAILURE);
    }

    printf("ACCOUNT HAS BEEN UPDATED");

    /*Close the database*/
    sqlite3_close(db);

    printf("Press enter to continue...");
    getchar();
    getchar();
    clearScreen();

    return;
}

void delete(){
    char query[100];
    char name[20];
    sqlite3 * db;
    char *zErrMsg = 0;
    int deleteFlag = 0;

    printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2 DELETE EMPLOYEE ACCOUNT \xB2\xB2\xB2\xB2\xB2\xB2\xB2");
    printf("\n\nEnter Name Of Employee: ");
    scanf("%s", name);
    clearScreen();

    sprintf(query, "DELETE FROM COMPANY where NAME = '%s';", name);

    //Open database
    if(openDatabase(DATABASE, &db) == FALSE){
        exit(EXIT_FAILURE);
    }

    //Verify name is in database
    if(entryExists(name, db) == FALSE){
        printf("Entry with name \"%s\" not found.\n", name);
    }

    //Execute
    printf("DELETING EMPLOYEE ACCOUNT....");
    if(sqlite3_exec(db, query, NULL, 0, &zErrMsg) != SQLITE_OK){
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        exit(EXIT_FAILURE);
    }

    printf("ENTRY HAS BEEN REMOVED FROM DATABASE\n");
   
    /*Close the database*/
    sqlite3_close(db);

    printf("Press enter to continue...");
    getchar();
    getchar();
    clearScreen();

    return;
}

int openDatabase(char * filename, sqlite3 ** db){
    int rc = sqlite3_open(filename, db);
    if(rc){
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(*db));
        return FALSE;
    }

    return TRUE;
}

int executeCommand(char * query, sqlite3 * db){
    const char * data = "Callback function called";
    char *zErrMsg = 0;

    int rc = sqlite3_exec(db, query, callback, 0, &zErrMsg);
    if(rc != SQLITE_OK){
        fprintf(stderr, "SQL Error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        return FALSE;
    }

    return TRUE;
}

int main(int argc, char* argv[]) {
    sqlite3 * db;
    char *zErrMsg = 0;
    int rc;
    int userChoice;
    char *command;
    const char * data = "Callback function called";

    //Create table if it does not exist
    createTable();
    clearScreen();

    /* Open the database */
    rc = openDatabase("test.db", &db);

    /* prompt user for command */
    while(TRUE){
        printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2 WELCOME TO THE MAIN MENU \xB2\xB2\xB2\xB2\xB2\xB2\xB2");
        printf("\n\n1.Create Employee Account\n2.Update information of existing account\n3.Delete An Existing Account\n4.Check the details of existing account\n5.View Employees\n6.Exit\n\nEnter your choice: ");
        scanf("%d",&userChoice);
        clearScreen();

        switch(userChoice){
            case INSERT: 
                insert();
                break;
            case UPDATE:
                update();
                break;
            case DELETE:
                delete();
                break;
            case SELECT: 
                viewAccount();
                break;
            case DISPLAY:
                viewAll(); 
                break;
            case EXIT: 
                exit(EXIT_SUCCESS);
            default:
                fprintf(stdout, "Invalid Input!!\n");
                exit(EXIT_FAILURE);
        }
    }

    return EXIT_SUCCESS;
}