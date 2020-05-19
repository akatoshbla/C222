/**
* Assignment 1: Performance Metrics  
* File: asmt1_kopp.c 
* Programmer: David Kopp
* Date: 1/31/14
* Description: This program allows a user to input parameters and calculate CPI, T, and MIPS.
**/

#include <stdio.h>

// Global variables
int frequency;
int totalCycles;
int totalInstructions;

// Option #1 method
void parameters() {

// Declaring of local variables
   int i;
   int totalClasses;
   int cpi;
   int instructions;

// Initialization of variables
   instructions = 0;
   cpi = 0;
   frequency = 0;
   totalCycles = 0;
   totalInstructions = 0;

// Prompts and Scans for user input
   printf("\nEnter the number of instruction classes: ");
   scanf("%d", &totalClasses);
   printf("Enter the frequency of the machine (MHz): ");
   scanf("%d", &frequency);

// Loop to obtain user input for each class
   for (i = 1; i <= totalClasses; i++) {
      printf("Enter CPI of class %d: ", i);
      scanf("%d", &cpi);
      printf("Enter instruction count of class %d (millions): ", i);
      scanf("%d", &instructions);
         
   // Calculations for summations
      totalCycles += cpi * instructions;
      totalInstructions += instructions;
   }
}

// Option #2 method
void aveCPI() {

// Declaring of local variables
   float cpiAve;

// Initialization of variables
   cpiAve = 0;

// Calculation for average CPI
   cpiAve = totalCycles / (float)totalInstructions;

// Output to user
   printf("The average CPI of the sequence is: %.2f\n", cpiAve);
}

// Option #3 method
void executionTime() {

// Declaring of local variables
   float cpuTime;

// Initialization of variables
   cpuTime = 0;

// Calculation for CPU time
   cpuTime = (totalCycles / (float)frequency) * 1000;

// Output to user
   printf("The total CPU time of the sequence is: %.2f msec\n", cpuTime);
}

void mips() {

// Declaring of local variables
   float mIPS;

// Initialization of variables
   mIPS = 0;

// Calculation for MIPS
   mIPS = totalInstructions / (totalCycles / (float)frequency);

// Output to user
   printf("The total MIPS of the sequence is: %.2f\n", mIPS);
}

int main() {

// Declaring of local variable choice is user input for the menu selection
   int choice;
   char junkInput[256];

//Initialization of variable
   choice = 0;

// Loop for user menu
   while (choice != 5) {
      printf("\nMenu of Options:");
      printf("\n----------------");
      printf("\n1) Enter parameters");
      printf("\n2) Calculate average CPI of a sequence of instructions");
      printf("\n3) Calculate total execution time of a sequence of instructions");
      printf("\n4) Calculate MIPS of a sequence of instructions");
      printf("\n5) Quit\n\n");
      printf("Enter selection: ");
      scanf("%d", &choice);
   
   // This if statement clears the scanf buffer if the input is chars instead of ints or if the input is zero
      if (choice == 0) {
         fgets(junkInput, 256, stdin);
      }
      
   // Switch to drive the menu
      switch (choice) {
         case 1: parameters(); 
            break;
         case 2: aveCPI(); 
            break;
         case 3: executionTime(); 
            break;
         case 4: mips(); 
            break;
         case 5: 
            break;
         default: printf("Invalid user input!\n");
            break;
      }
      
      // Re-initializing local variable to reset the while loop's starting condition unless exiting program     
      if (choice != 5) {
         choice = 0;
      }
   }
   return 1;
}