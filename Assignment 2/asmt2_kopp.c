/**
* Assignment 2: Cache Memory 
* File: asmt2_kopp.c 
* Programmer: David Kopp
* Date: 2/26/14
* Description: This program allows a user to input an address and data value, which checks against a datatype cache(in memory) and main memory. The program checks
*              for hits in the cache.(Cache Simulation of direct mapping)
**/

#include <stdio.h>
#include <stdlib.h>

// Global Variables
int memorysize;
int cachesize;
int blocksize;
int rows;

int *mmlist = NULL;

// cache dynamic array
struct node {

   int tag;
   int *block;
} *clist = NULL;
typedef struct node line;

// Option #1
void parameters() {

// Declaring of local variables
   int i;

// Initialization of variables
   memorysize = 0;
   cachesize = 0;
   blocksize = 0;

// Prompts and Scans for user input
   printf("\nEnter main memory size (words): ");
   scanf("%d", &memorysize);
   printf("Enter cache size (words): ");
   scanf("%d", &cachesize);
   printf("Enter block size (words/block): ");
   scanf("%d", &blocksize);

// Allocation and initialization of space for main memory and cache
   mmlist = (int *)malloc(memorysize *sizeof(int));

// Calculations for rows
   rows = cachesize / blocksize;

// Loop
   for (i = 0; memorysize - 1 >= i; i++) {
      mmlist[i] = memorysize - i;
      clist = (line *)malloc(rows *sizeof(line));
   }

// Loop to initialize the rows
   for (i = 0; rows - 1 >= i; i++) {
      clist[i].block = NULL;
      clist[i].tag = -1;
   }
}

// Option #2 - Writing and reading from cache 
void cache()  {

// Declaring of local variables
   int i;
   int read;
   int baseaddress;
   int mmaddress;
   int signal;
   int dvalue;
   int mtctag;
   int mtcblock;
   int mtcword;

// Initialization of variables
   read = -1;
   baseaddress = 0;
   mmaddress = 0;
   signal  = -1;
   dvalue = -1;
   mtctag = 0;
   mtcblock = 0;
   mtcword = 0;

// Prompts and Scans for user input
   printf("Select read (0) or write (1): ");
   scanf("%d", &signal);

   if (signal == 0) {
      printf("\nEnter main memory address to read from: ");
      scanf("%d", &mmaddress);
   }
   
   else {
      printf("\nEnter main memory address to write to: ");
      scanf("%d",  &mmaddress);
      printf("Enter value to write: ");
      scanf("%d", &dvalue);
   }

// Calculations for translation from main memory to cache
   mtctag = mmaddress / cachesize;
   mtcblock = (mmaddress % cachesize) / blocksize;
   mtcword = mmaddress % blocksize;

// Three hit/miss cases for cache
// Case 1 miss in the cache because it is empty
   if (clist[mtcblock].tag  == -1)  {
      clist[mtcblock].block = (int *)malloc(blocksize *sizeof(int));
   }

// Case 2 miss in the cache due to non-matching tags
   if (clist[mtcblock].tag != mtctag) {
   
   // print msg read / write miss
      if (signal == 0) {
         printf("Read miss!");
      }
      
      else {
         printf("Write miss!");
         mmlist[mmaddress] = dvalue;
      }
   
   // Update of the tag in cache
      clist[mtcblock].tag  = mtctag;
   
   // Calculation for base address for the start of a block
      baseaddress = (mmaddress / blocksize) * blocksize;
   
   // Setting up the addresses for the blocks in each row(line)
      for (i = 0; (blocksize - 1) >=  i; i++) {
         clist[mtcblock].block[i] = mmlist[baseaddress + i];
      }
   }
   
   // Case 3 hit in the cache
   else {
      read = clist[mtcblock].block[mtcword];
   
   // print msg read / write miss
      if (signal == 0) {
         printf("Read hit!");
      }
      
      else {
         printf("Write hit!");
      
         if (read != dvalue) {
            clist[mtcblock].block[mtcword] = dvalue;
         //clist[mtcblock].tag = mtctag;
         
         // Update main memory
            mmlist[mmaddress] = dvalue;
         }
         
         else  { }
      }
   }

   printf("\nWord %d of block %d with tag %d contains value %d\n", mtcword, mtcblock, clist[mtcblock].tag, clist[mtcblock].block[mtcword]);
}

int main() {

// Declaring of local variable choice is user input for the menu selection
   int choice;

//Initialization of variable
   choice = 0;

// Loop for user menu
   while (choice != 3) {
      printf("\nCache memory allocation and mapping:");
      printf("\n------------------------------------");
      printf("\n1) Enter parameters");
      printf("\n2) Access cache for reading/writing and transfer data");
      printf("\n3) Quit\n\n");
      printf("Enter selection: ");
      scanf("%d", &choice);
   
   // Switch to drive the menu
      switch (choice) {
         case 1: parameters();
            break;
         case 2: cache();
            break;
         case 3:
            break;
         default: printf("Invalid user input!\n");
            break;
      }
   }
   return 1;
}