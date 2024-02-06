/*
 * Common.h
 *
 *  Created on: Jan 7, 2024
 *      Author: willi
 */

#ifndef INCLUDES_COMMON_H_
#define INCLUDES_COMMON_H_

struct Date {
    int month;
    int day;
    int year;
};

struct Customer {
    char name[60];
    int acc_no;
    int age;
    char address[60];
    char citizenship[16];
    char acc_type[11];
    char phone[11];
    float amt;
    char dob[11];
    struct Date deposit;
};

enum boolean{true = 1, false = 0};
enum UpdateType {PHONE = 1, ADDRESS, TRANSACTION};

#endif /* INCLUDES_COMMON_H_ */
