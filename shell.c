#include <stdlib.h>
#include <stdio.h>
#include "interpreter.h"
#include "shellmemory.h"

int parse(char buffer[], char arg0[], char arg1[], char arg2[], char arg3[]) {
	int i = 0, j;

	// skip white space
	
	while(i<1000 && buffer[i]==' ') i++;

	// extract argo0
	
	j = 0;

	while(i<1000 && buffer[i]!=' ' && buffer[i]!='\n' && buffer[i]!='\r') {
		arg0[j] = buffer[i];
		j++; i++;
	}

	arg0[j] = '\0';

	while(i<1000 && buffer[i]==' ' && buffer[i]!='\n' && buffer[i]!='\r') 
		i++;

	// extract arg1
	
	j = 0;

	while(i<1000 && buffer[i]!=' ' && buffer[i]!='\n' && buffer[i]!='\r') {
		arg1[j] = buffer[i];
		j++; i++;
	}

	arg1[j] = '\0';

	while(i<1000 && buffer[i]==' ' && buffer[i]!='\n' && buffer[i]!='\r') 
		i++;

	// extract arg2
	
	j = 0;

	while(i<1000 && buffer[i]!=' ' && buffer[i]!='\n' && buffer[i]!='\r') {
		arg2[j] = buffer[i];
		j++; i++;
	}

	arg2[j] = '\0';

	while(i<1000 && buffer[i]==' ' && buffer[i]!='\n' && buffer[i]!='\r') 
		i++;

	// extract arg3
	
	j = 0;

	while(i<1000 && buffer[i]!=' ' && buffer[i]!='\n' && buffer[i]!='\r') {
		arg3[j] = buffer[i];
		j++; i++;
	}

	arg3[j] = '\0';

	while(i<1000 && buffer[i]==' ' && buffer[i]!='\n' && buffer[i]!='\r') 
		i++;

	// debug code: printf("[%s] [%s] [%s]\n", arg0, arg1, arg2);

	// check if there is more data (illegal)
	
	if (i==1000 || buffer[i]=='\n' || buffer[i]=='\r' || buffer[i]=='\0')
		return 1; // completed successfully (true)
	else
		return 0;
}

int prompt(char buffer[]) {
	char buf0[100], buf1[100], buf2[100], buf3[100];
	int result = 0;

	result = parse(buffer,buf0,buf1,buf2,buf3);

	if (!result)
		printf("Error: Command %s has too many characters\n",buffer);

	result = interpreter(buf0,buf1,buf2,buf3);

	if (result == 99) return 99;
	if (result == 98) printf("Command does not exist\n");
	if (result ==  1) printf("Wrong number of set parameters\n");
	if (result ==  2) printf("Wrong number of print parameters\n");
	if (result ==  3) printf("Run is  missing filename\n");
	if (result ==  4) printf("Script filename not found\n");
	if (result ==  5) printf("The exec progam was not found\n");

	return 0;
}

void remove_directory(){
   #ifdef __linux__
       system("rm -r BakcingStore");
   #else
       system("rmdir BackingStore /s");
   #endif
}

int shell() {
	char buffer[1000], buf0[100], buf1[100], buf2[100];
	int done = 0, result = 0;

	initShellMemory();

	printf("Welcome to the Tracy'shell!\n");
	printf("Version 3.0 Created March 2019\n");

	while(!done) {
		printf("$ ");
		fgets(buffer,999, stdin);

		result = prompt(buffer);

		if (result == 99) done = 1;
	}


	printf("Good bye.\n");
	remove_directory();//Delete the BackkingStore directory when exit.
	return 0;
}

