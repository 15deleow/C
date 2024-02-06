#include "studentRecords.h"

int main(void){
    //open input.dat for reading
    FILE * input = fopen("input.dat", "r");

    //open output.dat for writing
    FILE * output = fopen("output.dat", "w");

    //read 5 sets of data from input.dat
    int dataCount = 5;
    struct records data[dataCount];
    
    for(int i = 0; i < 5; i++){
        data[i].id = read_integer(input);
        data[i].gpa = read_double(input);
        data[i].classStanding = read_integer(input);
        data[i].age = read_double(input);
        readSeparater(input);
    }

    //Calculate the sum of GPAs
    double sumOfGpa = calculate_sum(data[0].gpa, data[1].gpa, data[2].gpa, data[3].gpa, data[4].gpa);

    //Calcualte the sum of the class standing
    double sumOfClassStanding = calculate_sum(data[0].classStanding, data[1].classStanding, data[2].classStanding, data[3].classStanding, data[4].classStanding);

    //Calculate the sum of the ages
    double sumOfAges = calculate_sum(data[0].age, data[1].age, data[2].age, data[3].age, data[4].age);

    // Calculates the mean of the GPAs, writing the result to the output file (output.dat);
    double meanOfGpas = calculate_mean(sumOfGpa, dataCount);
    print_double(output, meanOfGpas);

    // Calculates the mean of the class standings, writing the result to the output file (output.dat);
    double meanOfClassStanding = calculate_mean(sumOfClassStanding, dataCount);
    print_double(output, meanOfClassStanding);

    // Calculates the mean of the ages, writing the result to the output file (output.dat); 
    double meanOfAges = calculate_mean(sumOfAges, dataCount);
    print_double(output, meanOfAges);

    // Calculates the deviation of each GPA from the mean (Hint: need to call calculate_deviation ( ) 5 times) 
    double deviations[dataCount];
    for(int i = 0; i < dataCount; i++){
        deviations[i] = calculate_deviation(data[i].gpa, meanOfGpas);
    }

    // Calculates the variance of the GPAs Calculates the standard deviation of the GPAs, writing the result to the output file (output.dat); 
    double varianceOfGpa = calculate_variance(deviations[0],deviations[1],deviations[2],deviations[3],deviations[4], dataCount);
    double stdDevOfGpa = calculate_standard_deviation(varianceOfGpa);
    print_double(output, stdDevOfGpa);

    // Determines the min of the GPAs, writing the result to the output file (output.dat);
    double minGpa = find_min(data[0].gpa, data[1].gpa, data[2].gpa, data[3].gpa, data[4].gpa);
    print_double(output, minGpa);

    // Determines the max of the GPAs, writing the result to the output file (output.dat); 
    double maxGpa = find_max(data[0].gpa, data[1].gpa, data[2].gpa, data[3].gpa, data[4].gpa);
    print_double(output, maxGpa);

    // Closes the input and output files (i.e. input.dat and output.dat)
    fclose(input);
    fclose(output);

    return EXIT_SUCCESS;
}