/**
* Assignment 5: Pipelining/Superscalar Architecture
* File: asmt5_kopp.c 
* Programmer: David Kopp
* Date: 5/4/14
* Description: This program allows a user to input the number of instructions in a 6-stage pipeline architecture.
*              Then the user inputs the instructions and a Gantt chart is printed out for a single fetch pipeline and
*              a superscalar or double fetch unit pipeline.
**/

#include <stdio.h>
#include <stdlib.h>

// Global Variables
int maxInstr;

// Dynamic Array for storing registers for comparison
struct node {
int destReg;
int source1;
int source2;
int delay;
} *set = NULL;
typedef struct node instr;

// Option #1
void instructions() {
int i;

// Local Variables
char instrString[9];

// Prompt for number of instructions (n)
printf("\nEnter total number of instructions: ");
scanf("%d", &maxInstr);

// Assigning Memory Size for Dynamic Array instr
set = (instr *)malloc(maxInstr + 1 *sizeof(instr));

// For-Loop to input each instruction in dynamic array instr
printf("\n");
for (i = 1; i <= maxInstr; i++) {
printf("%d) ", i);
scanf("%s", instrString);

// Input for the Dynamic Array instr
set[i].destReg = instrString[1] - '0';
set[i].source1 = instrString[4] - '0';
set[i].source2 = instrString[7] - '0';
// printf("%d-%d-%d\n", set[i].destReg, set[i].source1, set[i].source2); 
}
}

// Gantt chart printout
void printChart(instr *set) {

// Local Variables
int i;
int k;

// Nested For-Loop to print out chart
for (i = 1; i <= maxInstr; i++) {
printf("%d)", i);

for (k = 1; k <= set[i].delay; k++) {
printf("\t");
}

printf("FI\tDI\tCO\tFO\tEI\tWO\n");
}
}

// Option #2
void pipeline() {

// Local Variables
int delay;
int overlap;
int totalDelay;
int i;

// Failsafe for Dynamic Array instr for first comparison
set[1].delay = 0;

// Initalization of overlap
overlap = 0;
totalDelay = 0;

// For-Loop to calculate overlap and delays
for (i = 2; i <= maxInstr; i++) {
delay = 0;
if ((set[i - 2].destReg == set[i].source1) || (set[i - 2].destReg == set[i].source2)) {
if (overlap == 0) {
delay = 1;
overlap = 1;
}

else {
delay = 0;
overlap = 0;
}
}

else {
overlap = 0;
}

if ((set[i - 1].destReg == set[i].source1) || (set[i - 1].destReg == set[i].source2)) {
delay = 2;
overlap = 1;
}

else { }

// Sets the delay in the dynamic array set
// printf("\n%d", delay);
set[i].delay = delay + set[i - 1].delay + 1;
// printf("\n%d", set[i].delay);
}

// Calculation for total delay in cycles
totalDelay = set[maxInstr].delay + 6;
 
// Printout for total cycles for n instructions
printf("\nTotal number of cycles: %d\n\n", totalDelay);
}

// Option #3
void superScalar() {

}

// Main method with menu
int main() {

// Local Variables
int choice;

// Initalization of Variables
choice = 0;

// Menu for user to make a choice
while (choice != 4) {
printf("\nPiplined/Superscalar instruction performence");
printf("\n--------------------------------------------");
printf("\n1) Enter instructions");
printf("\n2) Calculate/chart total cycles on a 6-stage pipelined architecture");
printf("\n3) Calculate/chart total cycles on a 6-stage superscalar architecture");
printf("\n4) Quit program");
printf("\n\nEnter selection: ");
scanf("%d", &choice);

// Switch for driving the user menu
switch(choice) {
case 1: instructions();
break;
case 2: pipeline(); printChart(set);
break;
case 3: superScalar();
break;
case 4: 
break;
default: printf("Invalid input!\n");
}
}

return 1;
}