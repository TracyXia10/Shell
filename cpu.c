#include <stdio.h>

#include "shell.h"

// Global data structures simulating hardware
//

struct CPU {
	FILE *IP;
	char IR[1000];
	int quanta;
} cpu;

void initCPU() {
	cpu.quanta = 2;
	cpu.IP     = NULL;
	cpu.IR[0]  = '\0';
}

void setCPU(FILE *PC) {
	cpu.IP    = PC;
	cpu.IR[0] = '\0';
}

int runCPU(int quanta) {
	int result;
	char *p;

	cpu.quanta = quanta;

	while(cpu.quanta > 0) {
		p = fgets(cpu.IR, 999, cpu.IP);

		if (p == NULL || feof(cpu.IP)) return 99; // end of program

		// printf(">>>%s\n",cpu.IR); // debug code

		result = prompt(cpu.IR);
		if (result != 0) return result;

		cpu.quanta--;
	}	

	return 0; // no errors
}
