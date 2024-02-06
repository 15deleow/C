#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#ifndef M_PI
#    define M_PI 3.14159265358979323846
#endif


void OhmsLaw(){
    int current, resistance, voltage;

    printf("Enter current value: ");
    scanf("%d", &current);

    printf("Enter resistance value: ");
    scanf("%d", &resistance);

    voltage = current & resistance;

    printf("Voltage = %d Volts\n", voltage);
}

void getPower(){
    int voltage, resistance, power;

    printf("Enter Voltage: ");
    scanf("%d", &voltage);
    printf("Enter resistance: ");
    scanf("%d", &resistance);

    power = (voltage * voltage) / resistance;
    printf("Power = %d W", power);
}

void polynomialCalc(){
    int x,a,b,c,d;

    printf("Enter values for the equation: y = 3 * ax^3 + (1/4) * bx^2 + 10 * cx + (-5) * d\n");
    printf("Enter 'a' value: ");
    scanf("%d", &a);

    printf("Enter 'b' value: ");
    scanf("%d", &b);

    printf("Enter 'c' value: ");
    scanf("%d", &c);

    printf("Enter 'd' value: ");
    scanf("%d", &d);

    printf("Enter 'x' value: ");
    scanf("%d", &x);

    // Calculate the y value
    int y = 3 * a * x * x * x + (1.0/4) * b * x * x + 10 * c * x + (-5) * d;

    // Print the result
    printf("For x = %d, y = %d\n", x, y);
}

void calculateCircumference(){
    float radius;
    float circumference;

    printf("Enter radius of circle: ");
    scanf("%f", &radius);

    circumference = 2.0 * M_PI * radius;
    printf("Circumference of Circle is %f\n", circumference);
}

int main(void){
    int numOne, numTwo;
    float numOneFloat, numTwoFloat;

    // printf("Please Enter an Integer: ");
    // scanf("%d", &numOne);

    // printf("Please Enter an Integer: ");
    // scanf("%d", &numTwo);

    // printf("Please Enter a float number: ");
    // scanf("%f", &numOneFloat);

    // printf("Please Enter a float number: ");
    // scanf("%f", &numTwoFloat);

    // printf("%d + %d = %d\n", numOne, numTwo, numOne + numTwo);
    // printf("%f - %f = %f\n", numOneFloat, numTwoFloat, numOneFloat - numTwoFloat);
    // printf("%d * %f = %d\n", numOne, numOneFloat, numOne * numOneFloat);
    // printf("%d / %d = %d (%f)\n", numOne, numTwo, numOne / numTwo, numOne / numTwo);
    // printf("%d / %f = %d (%f)\n", numOne, numTwoFloat, numOne / numTwoFloat);
    // printf("(float)%d / %d = %f\n", numOne, numTwo, (float)numOne / numTwo);

    // //Calculate mod of floats
    // fmod(numOneFloat, numTwoFloat) ? printf("0\n") : printf("1\n");

    // printf("*******Calculate Ohms******\n");
    // OhmsLaw();
    // printf("\n\n");

    // printf("*******Calculate Power******\n");
    // getPower();
    // printf("\n\n");

    printf("*******Calculate Polynomial******\n");
    polynomialCalc();
    printf("\n\n");

    printf("*******Calculate Circumference******\n");
    calculateCircumference();
    printf("\n\n");

    return EXIT_SUCCESS;
}