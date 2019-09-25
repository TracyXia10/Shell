#include<stdio.h>
typedef struct PCB_REC {
	FILE *PC;
	int start; // startAddressRAM
	struct PCB_REC *next;
	int pageTable[10];
} PCB;

void addToReady(PCB *p);
PCB *getFromReady();
PCB *makePCB(FILE *p, int startAddressRAM);
PCB *getHead();
void printPCB();
