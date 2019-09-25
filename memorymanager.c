#include <stdio.h>
#include <sys/stat.h>

#include "memorymanager.h"
#include "ram.h"


int countTotalPages(FILE *f){
	int lines=0;
	char c;

    // Extract characters from file and store in character c 
    for (c = getc(f); c != EOF; c = getc(f)){
        if (c == '\n'){lines = lines +1;}  
    }

    return lines/4;
}




int findFrame(FILE *page){
	int i;

	if (page == NULL) return -2; // error 
	
	for(i=0; i<10 && ram[i]!=NULL; i++); // find next available space

	if (i<10) {
		return i; // position in RAM
	}
	else
		return -1; // out of memory error
}

int cfileexists(const char* filename){
    struct stat buffer;
    int exist = stat(filename,&buffer);
    if(exist == 0)
        return 1;
    else // -1
        return 0;
}

int launcher(FILE *p){
	if(p == NULL){
		return 0;
	}
	int PC_page;
	int PC_offset;
	int pages_max;
	char c;
	FILE *to;

	if(cfileexists("./BackingStore/p1.txt") == 0){
		to = fopen("./BackingStore/p1.txt","w");
	}else if(cfileexists("./BackingStore/p2.txt") == 0){
		to = fopen("./BackingStore/p2.txt","w");
	}else{
		to = fopen("./BackingStore/p3.txt","w");
	}



	do{
  	c = getc(p);
  	putc(c, to);
	}
	while(c != EOF);

	fclose(to);
	return 1;


}