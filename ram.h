#include<stdio.h>
//Global variable.
extern FILE *ram[10];
// Public functions
//

void initRAM();
int addToRAM(FILE *p); // return startAddress or error codes
void clearRAM(int startAddressRAM);
