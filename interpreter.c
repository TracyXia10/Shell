#include<stdlib.h>
#include<stdio.h>
#include<string.h>

#include "shellmemory.h"
#include "shell.h"
#include "kernel.h"
#include "memorymanager.h"

int run(char *filename) {
	FILE *ptr;
	char buffer[1000], buf0[100], buf1[100], buf2[100];
	int result = 0;

	ptr = fopen(filename,"rt");
	if (ptr == NULL) return 4; // file not found

	fgets(buffer,999,ptr);
	while(!feof(ptr)) {
		if (strlen(buffer)>1) result = prompt(buffer);
		if (result == 99) break;
		fgets(buffer,999,ptr);
	}

	fclose(ptr);

	if (result == 99) return 99;

	return 0;
}

int exec(char *file1, char *file2, char *file3) {
	int result = 0;
	int result2 = 0; 
	FILE *p1, *p2, *p3;

	if (strlen(file1)<1) file1 = NULL;
	if (strlen(file2)<1) file2 = NULL;
	if (strlen(file3)<1) file3 = NULL;

	// Determine if there are duplicates and remove
	//We can remove the same file multiple times
	//if (file1!=NULL && file2!=NULL && strcmp(file1,file2)==0) file2=NULL;
	//if (file1!=NULL && file3!=NULL && strcmp(file1,file3)==0) file3=NULL;
	//if (file2!=NULL && file3!=NULL && strcmp(file2,file3)==0) file3=NULL;

	printf("f1:%s f2:%s f3:%s\n", file1, file2, file3);

	// Add to ready queue each  unique programs
	if (file1!=NULL) {
		p1 = fopen(file1,"rt");
		result = myinit(p1);
		result2 = launcher(p1);
		if(result2 == 0){
			printf("%s does not exits.\n", file1);
		}
		fclose(p1);
	}
	if (file2!=NULL) {
		p2 = fopen(file2,"rt");
		result = myinit(p2);
		result2 = launcher(p2);
		if(result2 == 0){
			printf("%s does not exits.\n", file2);
		}
		fclose(p2);
	}
	if (file3!=NULL) {
		p3 = fopen(file3,"rt");
		result = myinit(p3);
		result2 = launcher(p3);
		if(result2 == 0){
			printf("%s does not exits.\n", file3);
		}
		fclose(p3);
	}

	if (result > 0) scheduler();

	return 0;
}

int interpreter(char buf0[], char buf1[], char buf2[], char buf3[]) {
	int result = 0; // no errors

	if (strcmp(buf0,"help")==0) {
		printf("Legal commands:\n");
		printf("help              display this help\n");
		printf("quit              exits the shell\n");
		printf("set VAR STRING    assign STRING to VAR\n");
		printf("print VAR         display contents of VAR\n");
		printf("run SCRIPT.TXT    interpret SCRIPT.TXT\n");
		printf("exec P1 P2 P2     can run up to 3 distinct programs\n");

		result = 0;
	}
	else if (strcmp(buf0,"quit")==0) {
		result = 99; // exit shell code
	}
	else if (strcmp(buf0,"set")==0) {
		if (strlen(buf1)<1 || strlen(buf2)<1) return 1; // set error

		add(strdup(buf1), strdup(buf2));
	}
	else if (strcmp(buf0,"print")==0) {
		if (strlen(buf1)<1) return 2; // print error

		printf("%s\n", get(buf1));
	}
	else if (strcmp(buf0,"run")==0) {
		if (strlen(buf1)<1) return 3; // run error

		result = run(buf1);
	}
	else if (strcmp(buf0,"exec")==0) {
		if (strlen(buf1)<1) return 5; // exec error

		result = exec(buf1, buf2, buf3);
	}
	else {
		result = 98; // command does not exist
	}

	return result;
}

