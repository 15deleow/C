#ifndef DATABASEHANDLER_H
#define DATABASEHANDLER_H

#define DATABASE "record.db"

#include "sqlite3.h"
#include <stdlib.h>
#include <stdio.h>
#include "Common.h"
#include <string.h>

void createDatabase(void);

int getData(struct Customer * customer, int accountNumber);

void addAccount(char * sqlStmt);

void deleteAccount(const int accountNumber);

int displayAllAccounts();

int displayAccount(const int accountNumber);

int displayAccountByName(const char * userName);

int updateAccount(int, char *, const int);

int entryExists(int accountNumber);

int nameEntryExists(char * name);

#endif
