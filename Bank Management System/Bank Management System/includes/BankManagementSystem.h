#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "Common.h"

#ifndef MYHEADER_H
#define MYHEADER_H

int i;
int j;
int main_exit;

struct Customer add, upd, check, rem, transaction;

//Declarations
void clearStdinBuffer(void);

void writeCustomer(struct Customer *customer);

int readCustomer(struct Customer *customer);

void clearScreen();

float interest(float t,float amount,int rate);

void fordelay(int j);

void getAccountInfo(struct Customer *customer);

void new_acc();

void view_list();

void edit(void);

void transact(void);

void erase(void);

void see(void);

void close(void);

void menu(void);

void start(void);

#endif // MYHEADER_H
