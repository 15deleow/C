#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <conio.h>

#ifndef M_PI
#    define M_PI 3.14159265358979323846
#endif

#define TRUE 1
#define FALSE 0

void calculateForce(){
    printf("========== Newton's Second Law ==========\n\n");
    float mass, acceleration;

    printf("Please enter the mass and acceleration <0.0>: ");
    scanf("%f %f", &mass, &acceleration);

    float force = mass * acceleration;

    printf("force = mass * acceleration = %f * %f = %fN\n\n", mass, acceleration, force);
    printf("=========================================\n");
}

void volumeEquation(){
    float radius, height;

    printf("========== Volume of a Cylinder ==========\n\n");

    printf("Please enter the radius and height of cylinder <0.0>: ");
    scanf("%f %f", &radius, &height);
    float volume = radius * radius * height * M_PI;
    printf("volume = PI * radius^2 * height = %f * %f^2 * %f = %fm^3\n", M_PI, radius, height, volume);

    printf("==========================================\n");
}

void characterEncoding(){
    char plainText, encodedChar;
    int shift;
    printf("========== Character Encoding ==========\n\n");
    printf("Please enter character to encode: ");
    
    //Consume the newline character from previous input
    getchar();
    plainText = getchar();

    printf("Please enter shift key value: ");
    scanf("%d", &shift);

    //Calculates offset of plainText from uppercase letter A
    int offsetChar = plainText - 'A';
    //Get ASCII value of the given character
    int asciiValue = offsetChar + 'a';

    //Encodes the character by subtracting ASCII value by shift
    encodedChar = (char)asciiValue - shift;

    printf("encodedChar = (%c - 'A') + 'a' - %d = %c\n", plainText, shift, encodedChar);

    printf("==========================================\n");
}

void distanceBetweenTwoPoints(){
    printf("========== Distance Between Two Points ==========\n\n");
    float distance, x1, x2, y1, y2;

    printf("Please enter both coordinates <x1 y1 x2 y2>: ");
    scanf("%f %f %f %f", &x1, &y1, &x2, &y2);

    float diffX = x1 - x2;
    float diffY = y1 - y2;
    float xSquared = pow(diffX, 2);
    float ySquared = pow(diffY, 2);
    distance = sqrt(xSquared + ySquared);

    printf("distance = sqrt((%.2f - %.2f)^2 + (%.2f - %.2f)^2) = %f\n", x1, x2, y1, y2, distance);

    printf("=================================================\n");
}

void Tangent(){
    printf("========== Tangent ==========\n\n");
    float tan_theta, theta;

    printf("Please enter the theta value in degrees: ");
    scanf("%f", &theta);

    //Convert degree to radians
    theta = theta * M_PI / 180.0;

    tan_theta = sin(theta) / cos(theta);
    printf("tan(%f) = sin(%f) / cos(%f) = %f\n\n", theta, theta, theta, tan_theta);

    printf("=============================\n");
}

void equivalentParallelResistance(){
    printf("========== Equivalent Parallel Resistance ==========\n\n");
    int r1, r2, r3;
    float parallelResistance;

    printf("Please enter resistor values <R1 R2 R3>: ");
    scanf("%d %d %d", &r1, &r2, &r3);

    parallelResistance = 1.0 / (1.0 / r1 + 1.0 / r2 + 1.0 / r3);

    printf("parallel_resistance = 1/(1/%d + 1/%d + 1/%d) = %f ohms\n\n", r1, r2, r3, parallelResistance);
    printf("====================================================\n");
}

void generalEquation(){
    // int a;
    // float y, z, x, ans;

    printf("========== General Equation ==========\n\n");
    
    int a;
    float x, y, z;

    // Prompt the user to enter values for a, x, y, and z
    printf("Enter values for a, x, y, z (separated by spaces): ");
    scanf("%d %f %f %f", &a, &x, &y, &z);

    // Calculate the value of the equation
    int partOne = ((float)2 / (float)3) - y;
    int partTwo = z * x / (a % 2); 
    float ans = partOne + partTwo + M_PI;

    // Display the result
    printf("y = (2/3) - y + z * x / (a %% 2) + PI = (2/3) - %f - %f * %f / (%d %% 2) + PI = %f\n\n", y, z, x, a, ans);

    printf("======================================\n");
}

void continueKey(void){
    printf("Press any key to continue . . .");
    getch();
    printf("\n");
}

int menu(){
    int userChoice;
    printf("=========================================\n");
    printf("|\t\tEQUATIONS MENU\t\t|\n");
    printf("=========================================\n\n");

    printf("\t1. Force Equation\n");
    printf("\t2. Volume Equation\n");
    printf("\t3. Character Encoding\n");
    printf("\t4. Distance Between Two Points\n");
    printf("\t5. Tangent Equation\n");
    printf("\t6. Equivalent Parallel Resistance\n");
    printf("\t7. General Equation\n");
    printf("\t8. Exit\n\n");
    printf("Please Enter Option: ");
    scanf("%d", &userChoice);

    return userChoice - 1;
}

int main(void){
    void (*functionList[8])() = {calculateForce, volumeEquation, characterEncoding, distanceBetweenTwoPoints, Tangent, equivalentParallelResistance, generalEquation, exit};
    
    while(TRUE){
        functionList[menu()]();
        printf("\nHit any button to continue...");
        getch();
        system("cls");
    }
    return EXIT_SUCCESS;
}