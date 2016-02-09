#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <unistd.h>
int loopMod(a,b){return ((a%b)+b)%b;} //for looping around

void intro(void){
	printf("Adjust screen size and press enter.");
	getchar();
}

int getSize(){ //get terminal width
	struct winsize terminalSize;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &terminalSize);
	return terminalSize.ws_col;
}

void initializeArray(char* a, int size){
	int i;
	for(i=0;i<size;i++){
		a[i]=0;
	}
	a[size/2]=1;
}

void waitTillNextUpdate(){
		// I put the newline inside this procedure so that I
		// could easily switch between getchar and sleep.
	usleep(50*1000); printf("\n");
	//getchar(); 
	return;
}

char updateChar(char l,char c,char r){
	return  
			// choose one of the following:
		//(c||l) != (c||r); //thin triangles
		//(c!=l) || (c!=r);  //thick triangles
		//(c != l != r);  //weird triangles
		//!(c && l && r) && (c || r); //turing complete
		//(c||l) != (r); //pseudo random
		(105
		>>(((!!l)<<2)|((!!c)<<1)|((!!r)<<0)))&1;
}
void updateArray(char* prev,char* next, int size){
	int i;
	for(i=0;i<size;i++){
		next[i]=updateChar(
							prev [loopMod(i-1,size)],
							prev [i],
							prev [loopMod(i+1,size)]);
	}
}


char* printChar(char a){
	
	
	printf("%s", a?"﻿＃":"﻿．" );
	//printf("%s", a?"﻿#":"﻿ " );

}
void printArray(char a[],int size){
	int i;
	for(i=0;i<size;i++){
		printChar(a[i]);
	}
}

int main(void){
	intro();
	int size=getSize();
	char* arrayA=(char*)malloc(size);
	char* arrayB=(char*)malloc(size);
	initializeArray(arrayA,size);
	getchar();
	
	while(1){
		printArray(arrayA,size);
		updateArray(arrayA,arrayB,size);
		{
			char * temp=arrayA;  //swap
			arrayA=arrayB;
			arrayB=temp;	
		}
		waitTillNextUpdate();
	}
}
