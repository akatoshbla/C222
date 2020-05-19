/**
* Assignment 4: Virtual Memory
* File: asmt4_kopp.c 
* Programmer: David Kopp
* Date: 3/25/14
* Description: This program allows a user to input parameters for a virtual address. Then it maps the address to see if there is a hit or page fault.
**/

#include <stdio.h>
#include <stdlib.h>

// Global vars
int mmSize;
int pageSize;
int rPolicy;
int entries;

// Structure format for the dynamic array
struct node {
   int vp;
   int pf;
} *pageTable = NULL;
typedef struct node row;

// Option #1
void parameters()  {

// Local vars
   int i;

// Initialization of vars
   mmSize = 0;
   pageSize = 0;
   rPolicy = 0;
   entries = 0;

// Prompts for user input of main memory size, page size, and replacement policy
   printf("\nEnter main memory size (words): ");
   scanf("%d", &mmSize);
   printf("Enter page size (words/page): ");
   scanf("%d", &pageSize);
   printf("Enter replacement policy (0=LRU, 1=FIFO): ");
   scanf("%d", &rPolicy);

// Calculation for number of entries for the page table
   entries = mmSize / pageSize;

// Allocation of space for the page table
   pageTable = (row *)malloc(entries *sizeof(row));

// Initialization of the VP fields to -1 in page table
   for (i = 0; i <= entries - 1; i++) {
      pageTable[i].vp = -1;
   }
}

// Option #2
void mapping() {

// Local vars
   int virtualMA;
   int index;
   int virtualPage;
   int offset;
   int i;
   int pfCopy;
   int pAddress;


// Initialization of vars
   virtualMA = -1;
   index = 0;
   virtualPage = -1;
   offset = -1;
   pfCopy = -1;
   pAddress = -1;


// Prompt for virtual memory address
   printf("Enter virtual memory address to access: ");
   scanf("%d", &virtualMA);

// Translation of virtual memory address into virtual page and offset
   virtualPage = virtualMA / pageSize;
   offset = virtualMA % pageSize;

// While loop to check for the virtual page in the page table
   while ((index < entries) && (pageTable[index].vp != -1) && (pageTable[index].vp != virtualPage)) {
      index++;
   }

// Check for case #1: Page fault: non-matching entry 
   if (index == entries) {
      pfCopy = pageTable[0].pf;
   
   // For loop that moves the entries up and leaves the last spot open
      for (i = 0; i <= entries - 2; i++) {
      //  pageTable[i].vp = pageTable[i + 1].vp;
      //  pageTable[i].pf = pageTable[i + 1].pf;
         pageTable[i] = pageTable[i + 1];
      }
   
   // Moves new address into the list and assigns the page frame to be the override's top entry page frame
      pageTable[entries - 1].vp = virtualPage;
      pageTable[entries - 1].pf = pfCopy;
   
   // Message to user about VA mapping status
      printf("Page fault!");
   }
   
   // Check for case #2: Page fault: unused entry -- page table is empty
   else if (pageTable[index].vp == -1) {
      pageTable[index].vp  = virtualPage;
      pageTable[index].pf = index;
   
   // Message to user about VA mapping status
      printf("Page fault!");
   }
   
   // Check for case #3: Hit: matching entry found
   else {
   
   // Replacement policy LRU with page frame save of index
      if (rPolicy == 0) {
         pfCopy = pageTable[index].pf;
      
      // for loop to move up entries and place the copyed pf where the matching entry was found
         for (i = index; i <= entries - 2; i++) {
            if (pageTable[i].vp == -1) { 
               break;
            }
         
         // Moves the entries up
            pageTable[i] = pageTable[i + 1];
         }
      
      // Inserts the entry into the bottom of the page table
         pageTable[i].vp = virtualPage;
         pageTable[i].pf = pfCopy;
      }
   
   // Calculation for physical address
      pAddress = pfCopy * pageSize + offset;
   
   // Message to user about VA mapping status
      printf("Virtual address %d maps to physical address %d", virtualMA, pAddress);
   }
}

// Option #3 printing the page table
void print() {

// Local vars
   int i;

// Initialization of vars


// Print out loop
   for (i = 0; i <= entries - 1; i++) {
      if (pageTable[i].vp == -1) { 
         break; 
      }
   
      printf("\nVP %d --> PF %d", pageTable[i].vp, pageTable[i].pf);
   }
}

int main() {

// Declaring of local variable choice is user input for the menu selection
   int choice;

// Initialization of variable
   choice = 0;

// Loop for user menu
   while (choice != 4) {
      printf("\n\nVirtual memory to Main memory mapping:");
      printf("\n--------------------------------------");
      printf("\n1) Set parameters");
      printf("\n2) Map virtual address");
      printf("\n3) Print page table");
      printf("\n4) Quit\n\n");
      printf("Enter selection: ");
      scanf("%d", &choice);
   
   // Switch to drive the menu
      switch (choice) {
         case 1: parameters();
            break;
         case 2: mapping();
            break;
         case 3: print();
            break;
         case 4:
            break;
         default: printf("Invalid user input!\n");
            break;
      }
   }
   return 1;
}