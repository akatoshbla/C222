/**
* Assignment 3: Hamming Code 
* File: asmt3_kopp.c 
* Programmer: David Kopp
* Date: 3/7/14
* Description: This program allows a user to input a hamming code. Then the program checks the code and corrects it if invalid.
**/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// Global Variables
int maxLength;
int parity;

// Initialization of global variables

// Dynamic string array that holds chars
char *hammingString = NULL;


// Option #1
void parameters() {

// Declaring of local variables

// Initialization of variables

// Printout and scans of hamming code
printf("\nEnter maximum length: ");
scanf("%d", &maxLength);
printf("Enter the parity (0 = even, 1 = odd): ");
scanf("%d", &parity);

// Allocation of memory for string / char array
hammingString = (char *)malloc(maxLength *sizeof(char));
}

// Option #2
void hammingCode() {

// Declaring of local variables
int i;
int j;
int k;
int actualLength;
int parityResult;
int result;
int totalParityBits;

// Initialization of variables
actualLength = 0;
result = 0;
totalParityBits = 0;

// Printout and scan to recieve hamming code into the array
printf("Enter Hamming code: ");
scanf("%s", hammingString);

// Calculation of the length of the user inputed code
actualLength = strlen(hammingString);

// Calculations of total parity bits needed
totalParityBits = ceil(log(actualLength) / log(2));

// Loops to check for Hamming code error
for (i = 1; i < actualLength; i *= 2) {
parityResult = parity;
for (j = i; j <= actualLength; j += i*2) {
for (k = j; (k < i + j) && (k <= actualLength); k++) { 
//printf("\n%d", k); // Debug to see if we are getting all the correct bits checked
parityResult =  parityResult ^ (hammingString[actualLength - k] - '0');
}
}

// Update result
result = result + parityResult  * i;
}

// Check if there is no error or there is an error that was corrected
if (result == 0) {
printf("There is no bit error");
}

else { 
printf("There is an error in bit: %d", result);

// Correction of the Hamming code
//hammingString[actualLength - result] = '1' - hammingString[actualLength - result]; // Check and Fix
if (hammingString[actualLength - result] == '1') {
hammingString[actualLength - result] = '0';
}

else {
hammingString[actualLength - result] = '1';
}

printf("\nThe corrected Hamming code is: %s", hammingString);
}
}

int main() {

// Declaring of local variable choice is user input for the menu selection
int choice;

//Initialization of variable
choice = 0;

// Loop for user menu
while (choice != 3) {
printf("\n\nHamming Code Checker:");
printf("\n---------------------");
printf("\n1) Enter parameters");
printf("\n2) Check Hamming code");
printf("\n3) Quit\n\n");
printf("Enter selection: ");
scanf("%d", &choice);
   
// Switch to drive the menu
switch (choice) {
case 1: parameters();
break;
case 2: hammingCode();
break;
case 3:
break;
default: printf("Invalid user input!\n");
break;
}
}

return 1;
}