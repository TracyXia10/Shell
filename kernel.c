#include<stdlib.h>
#include<stdio.h>

#include "shell.h"
#include "ram.h"
#include "cpu.h"
#include "pcb.h"
#include "memorymanager.h"

int myinit(FILE *p) {
	PCB *pcb;
	int result;

	result = addToRAM(p);

	if (result>=0) {
		pcb = makePCB(p,result);
		if (pcb != NULL) {
			addToReady(pcb);
			return 1;
		}
	}

	return 0;
}

void terminate(PCB *p) {
	clearRAM(p->start);
	free(p);
}

void scheduler() {
	PCB *pcb;
	int result;

	// initialize CPU
	initCPU();

	// execute the processes
	while(getHead() != NULL) {
		// printPCB(); // for debugging

		pcb = getFromReady();

		if (pcb != NULL) {
			setCPU(pcb->PC);
			result = runCPU(2);

			if (result == 99) terminate(pcb);
			else addToReady(pcb);
		} 	
	}
}

void make_directory(const char* name){
   #ifdef __linux__
       mkdir(name, 777); 
   #else
       _mkdir(name);
   #endif
}


void boot(){
	int i;
	for(i=0; i<10; i++) ram[i] = NULL;
	make_directory("BackingStore");
}

int main() {
	boot(); 
	int result = 0;

	initRAM();
	initCPU();

	result = shell();

	return result;
}
