/**
 * Tanner Brown
 * TCSS 333 Assignment 1
 */


#include <stdio.h>
#include <stdbool.h>
#include <math.h>


double ParseEquation(char theEquation[]);
double BinaryToDec(char *theNum, int size, int decimalPoint);
double DoMath (double num1, double num2, char op);
void DecToBinary(double theNum);

/**
 * Main Function
 * @return n/a
 */
int main() {

    char op; //the operator
    double n1;
    double n2;
    double result = 0;
    char num1[50] = {'\0'}; //char array for first user number in expression
    char num2[50] = {'\0'}; //char array for second user number in expression


    printf("Enter an expression using BINARY numbers or Q to quit: ");
    scanf(" %s %c %s", num1, &op, num2);

    if(num1[0] != 'q' && num1[0] != 'Q') {

        n1 = ParseEquation(num1);
        n2 = ParseEquation(num2);

        printf("%f %c %f ", n1, op, n2);

        result = DoMath(n1, n2, op);

        printf(" = %f\n", result);
        printf("%s %c %s = ", num1, op, num2);

        DecToBinary(result);

    }
    return 0;
}


/**
 * Reads each number the user gives to determine its length and location of the
 * decimal point. It then passes that info into another function that converts
 * the numbers from binary and returns that to the main function.
 *
 * @param theNum - number given by user to be parsed, converted and calculated.
 * @return decimal conversion of the number the user gives.
 */
double ParseEquation(char *theNum) {

    bool loop = true;
    int decimalPoint = -99; //where the decimal point is in the array. -99 indicates no decimal.
    int arrayIndex = 0; //index of current array

    while(loop) {

        char currentChar = theNum[arrayIndex];

        if (currentChar == '.') {
            decimalPoint = arrayIndex;

        }else if(currentChar != '0' && currentChar != '1') {
            loop = false;
        }

        arrayIndex++;
    }

    if(decimalPoint == -99){
        decimalPoint = arrayIndex-1;
    }

    return BinaryToDec(theNum, arrayIndex-1, decimalPoint);

}

/**
 * This function converts an array of characters representing a binary
 * value and converts it to decimal.
 *
 * @param theNum - the number being converted.
 * @param size - the size of the array (that is being used by the number given)
 * @param decimalPoint - the location where the decimal is in the array
 * @return - a decimal value of the number the user gave.
 */
double BinaryToDec(char *theNum, int size, int decimalPoint){

    double decValue = 0;
    double tempVal = 0;
    int power = decimalPoint - 1;


    for (int i = 0; i < size; i++, power--){


        if(theNum[i] == '.'){
            i++;
        }

        if(theNum[i] == '1') {
            tempVal = pow(2, power);
            decValue = decValue + tempVal;
        }
    }
    return decValue;
}

/**
 * This function calculates the math equation defined by the user
 * after it has been converted from binary to decimal.
 * @param num1 - decimal value of the number on the left side of the operator.
 * @param num2 - decimal value of the number on the right side of the operator.
 * @param op - the math operator
 * @return - the result of the equation in decimal form.
 */
double DoMath(double num1, double num2, char op){

    if(op == '*') {

        return num1 * num2;

    }else if(op == '+') {

        return num1 + num2;

    }else if(op == '/') {
        return num1 / num2;
    }else if(op == '-') {
        return num1 - num2;
    }

    return 0;

}

/**
 * Final function converts the decimal result of the equation back
 * into binary form.
 * @param theNum - the answer to the equation in binary form.
 */
void DecToBinary(double theNum){

    char binArray[50] = {'\0'};

    int wholeNum = theNum/1; //get the numbers to the left of the decimal point
    double decimalNum = theNum - wholeNum; //get the numbers after the decimal point
    double power = 2;
    int i = 0;
    char tempBin;

    while (theNum > power){
        power = power * 2;
    }

    while (power > 1){
        power = power / 2;

        if(wholeNum >= power) {
            tempBin = '1';
            wholeNum -= power;
        } else {
            tempBin = '0';
        }

        binArray[i] = tempBin;
        i++;
    }

    //add decimal point and calculate decimal bin values
    binArray[i]='.';
    i++;
    if(decimalNum == 0){
        binArray[i] = '0';
    }

    while (decimalNum != 0) {
        power /= 2;
        if (decimalNum >= power) {
            tempBin = '1';
            decimalNum = decimalNum - power;
        } else {
            tempBin = '0';

        }

        binArray[i] = tempBin;
        i++;
    }


    printf("%s\n", binArray);

}
