#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <time.h>


int loopMod(a,b){return ((a%b)+b)%b;} //for looping around

int getSize(){ //get terminal width
	struct winsize terminalSize;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &terminalSize);
	return terminalSize.ws_col;
}

void initializeArray(char* a, int size){
	int i;
	srand(time(NULL));
	for(i=0;i<size;i++){
		a[i]=
		0;
		//(rand()%2);
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
unsigned char rule;
char updateChar(char l,char c,char r){
	return  
			// choose one of the following:
		//(c||l) != (c||r); //thin triangles
		//(c!=l) || (c!=r);  //thick triangles
		//(c != l != r);  //weird triangles
		//!(c && l && r) && (c || r); //turing complete
		//(c||l) != (r); //pseudo random
		(rule>>(((!!l)<<2)|((!!c)<<1)|((!!r)<<0)))&1;
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
	printf("%s", a?"█":" " );
}
void printArray(char a[],int size){
	int i;
	for(i=0;i<size;i++){
		printChar(a[i]);
	}
}

int main(int argc, char**argv){
	if(argc == 1){
		printf("please write the rule you want like:\n %s rule\n",argv[0]);
		return 1;
	}else
	{
		rule=(unsigned char)(atoi(argv[1]));
	}
	int size=getSize();
	char* arrayA=(char*)malloc(size);
	char* arrayB=(char*)malloc(size);
	initializeArray(arrayA,size);
	
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
