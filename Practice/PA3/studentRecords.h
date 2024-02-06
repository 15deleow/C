#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct records{
    int id;
    double gpa;
    enum {FRESHMAN = 1, SOPHOMORE, JUNIOR, SENIOR} classStanding;
    double age;
};

void readSeparater(FILE * infile);

/**
 *  Reads one double precision number from the input file.
*/
double read_double (FILE *infile);

/**
 *  Reads one integer number from the input file
*/
int read_integer (FILE *infile);

/**
 *  Finds the sum of given values and returns the result
*/
double calculate_sum (double number1, double number2, double number3, double number4, double number5) ;

/**
 *  Determines the mean through the calculation @param sum / @param number and returns result.
 *  If number is equal to zero, returns -1.0
*/
double calculate_mean (double sum, int number);

/**
 * Determines the deviation of @param number from the @param mean and returns the result.
*/
double calculate_deviation (double number, double mean);

/**
 * Determines the variance and returns the result.
*/
double calculate_variance (double deviation1, double deviation2, double deviation3, double deviation4, double deviation5, int number);

/**
 * Calculates the standard deviation and returns the result
*/
double calculate_standard_deviation (double variance);

/**
 * Determines the maximum number out of the five input parameters passed into the function and
 * returns this value.
*/
double find_max (double number1, double number2, double number3, double number4, double number5);

/**
 * Determines the minimum number out of the five input parameters passed into the function and
 * returns this value.
*/
double find_min (double number1, double number2, double number3, double number4, double number5);

/**
 * Prints a double precision number to an output file
*/
void print_double (FILE *outfile, double number);

